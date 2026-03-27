param(
    [string]$Handle = "JesusRac31",
    [string]$RootPath = "..",
    [switch]$DryRun
)

$ErrorActionPreference = "Stop"

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot $RootPath)).Path
$unfinishedComment = "//Eliminar comentario si el proyecto esta terminado (Dinamica empezo el 21/06/2024)"

function Get-Json([string]$url) {
    return Invoke-RestMethod -Uri $url -Method Get
}

function Parse-FolderRound([string]$folderName) {
    if ($folderName -match '^CF R\s+(\d+)') {
        return @{ Type = 'cf-round'; Number = [int]$matches[1] }
    }
    if ($folderName -match '^CF Global R\s+(\d+)') {
        return @{ Type = 'cf-global'; Number = [int]$matches[1] }
    }
    if ($folderName -match '^Educational CF R\s+(\d+)') {
        return @{ Type = 'edu'; Number = [int]$matches[1] }
    }
    if ($folderName -match '^CodeTON R\s+(\d+)') {
        return @{ Type = 'codeton'; Number = [int]$matches[1] }
    }
    if ($folderName -match '^Pinely R\s+(\d+)') {
        return @{ Type = 'pinely'; Number = [int]$matches[1] }
    }
    if ($folderName -match '^Hello\s+(\d+)') {
        return @{ Type = 'hello'; Number = [int]$matches[1] }
    }
    return $null
}

function Get-ContestIdFromFolder([string]$folderName, $contestList) {
    $parsed = Parse-FolderRound $folderName
    if (-not $parsed) { return $null }

    $num = $parsed.Number
    $regex = switch ($parsed.Type) {
        'cf-round' { "Codeforces Round\s+$num\b"; break }
        'cf-global' { "Codeforces Global Round\s+$num\b"; break }
        'edu' { "Educational Codeforces Round\s+$num\b"; break }
        'codeton' { "CodeTON Round\s+$num\b"; break }
        'pinely' { "Pinely Round\s+$num\b"; break }
        'hello' { "^Hello\s+$num\b"; break }
        default { $null }
    }

    if (-not $regex) { return $null }

    $candidates = $contestList | Where-Object { $_.name -match $regex }
    if (-not $candidates -or $candidates.Count -eq 0) { return $null }

    return ($candidates | Sort-Object id -Descending | Select-Object -First 1).id
}

function Parse-IndexCandidates([string]$fileName) {
    if ($fileName -notmatch '^([^\.]+)\.\s') { return @() }
    $token = $matches[1].Trim()

    if ($token -match '^([A-Z])1-2$') {
        $c = $matches[1]
        return @("${c}1", "${c}2")
    }

    if ($token -match '^[A-Z][0-9]?$') {
        return @($token)
    }

    return @($token)
}

function Parse-ProblemTitle([string]$fileName) {
    if ($fileName -match '^[^\.]+\.\s(.+)\.cpp$') {
        return $matches[1].Trim()
    }
    return $null
}

Write-Output "Cargando lista de concursos..."
$contestResponse = Get-Json "https://codeforces.com/api/contest.list?gym=false"
if ($contestResponse.status -ne 'OK') {
    throw "Error al consultar contest.list"
}
$contestList = $contestResponse.result

Write-Output "Cargando envios de $Handle..."
$allSubmissions = @()
$from = 1
$batch = 1000
while ($true) {
    $url = "https://codeforces.com/api/user.status?handle=$Handle&from=$from&count=$batch"
    $resp = Get-Json $url
    if ($resp.status -ne 'OK') { throw "Error al consultar user.status" }

    $chunk = $resp.result
    if (-not $chunk -or $chunk.Count -eq 0) { break }

    $allSubmissions += $chunk
    if ($chunk.Count -lt $batch) { break }
    $from += $batch
}

$acceptedSubs = $allSubmissions | Where-Object { $_.verdict -eq 'OK' -and $_.problem.contestId -and $_.problem.index }

$acceptedMap = @{}
$acceptedByNameAndIndex = @{}
foreach ($sub in $acceptedSubs) {
    $cid = [int]$sub.problem.contestId
    $idx = [string]$sub.problem.index
    $name = [string]$sub.problem.name
    $key = "$cid|$idx"
    if (-not $acceptedMap.ContainsKey($key)) {
        $acceptedMap[$key] = "https://codeforces.com/contest/$cid/problem/$idx"
    }

    $nameKey = "${idx}|${name}"
    if (-not $acceptedByNameAndIndex.ContainsKey($nameKey)) {
        $acceptedByNameAndIndex[$nameKey] = New-Object System.Collections.Generic.HashSet[int]
    }
    [void]$acceptedByNameAndIndex[$nameKey].Add($cid)
}

$exclude = @('Plantilla.cpp', 'test.cpp')
$files = Get-ChildItem -LiteralPath $repoRoot -Recurse -File -Filter *.cpp |
    Where-Object {
        $_.Name -notin $exclude -and
        $_.FullName -notmatch '\\.vscode\\' -and
        $_.FullName -notmatch '\\Tracking Readme\\'
    }

$folderContestId = @{}
$folders = $files | ForEach-Object { Split-Path ($_.FullName.Substring($repoRoot.Length + 1)) -Parent } | Select-Object -Unique
foreach ($f in $folders) {
    if ($f -eq 'Randoms') {
        $folderContestId[$f] = $null
    } else {
        $folderContestId[$f] = Get-ContestIdFromFolder $f $contestList
    }
}

$changed = 0
$skippedWithComment = 0
$unresolved = New-Object System.Collections.Generic.List[string]

foreach ($file in $files) {
    $raw = [System.IO.File]::ReadAllText($file.FullName)
    $lines = $raw -split "`r?`n"
    $nonEmpty = @($lines | Where-Object { $_.Trim() -ne '' })
    if ($nonEmpty.Count -eq 0) { continue }

    $last = $nonEmpty[-1].Trim()
    if ($last.StartsWith('//')) {
        $skippedWithComment++
        continue
    }

    $relative = $file.FullName.Substring($repoRoot.Length + 1)
    $folder = Split-Path $relative -Parent
    $contestId = $folderContestId[$folder]
    $indices = Parse-IndexCandidates $file.Name
    $title = Parse-ProblemTitle $file.Name

    $acceptedUrl = $null

    if ($contestId -and $indices.Count -gt 0) {
        foreach ($idx in $indices) {
            $k = "$contestId|$idx"
            if ($acceptedMap.ContainsKey($k)) {
                $acceptedUrl = $acceptedMap[$k]
                break
            }
        }
    }

    if (-not $acceptedUrl -and $indices.Count -gt 0 -and $title) {
        foreach ($idx in $indices) {
            $nameKey = "${idx}|${title}"
            if ($acceptedByNameAndIndex.ContainsKey($nameKey)) {
                $set = $acceptedByNameAndIndex[$nameKey]
                if ($set.Count -eq 1) {
                    $cid = ($set | Select-Object -First 1)
                    $acceptedUrl = "https://codeforces.com/contest/$cid/problem/$idx"
                    break
                }
            }
        }
    }

    $commentToAdd = if ($acceptedUrl) { "// $acceptedUrl" } else { $unfinishedComment }

    $eol = if ($raw -match "`r`n") { "`r`n" } else { "`n" }
    $newRaw = $raw
    if (-not $newRaw.EndsWith($eol)) {
        $newRaw += $eol
    }
    $newRaw += $commentToAdd + $eol

    if (-not $DryRun) {
        [System.IO.File]::WriteAllText($file.FullName, $newRaw, (New-Object System.Text.UTF8Encoding($false)))
    }
    $changed++

    if (-not $acceptedUrl -and -not $contestId -and $folder -ne 'Randoms') {
        $unresolved.Add($relative) | Out-Null
    }
}

Write-Output "Archivos con comentario final previo (sin tocar): $skippedWithComment"
Write-Output "Archivos actualizados: $changed"
if ($unresolved.Count -gt 0) {
    Write-Output "No se pudo mapear concurso por carpeta en $($unresolved.Count) archivos:"
    $unresolved | ForEach-Object { Write-Output "- $_" }
}