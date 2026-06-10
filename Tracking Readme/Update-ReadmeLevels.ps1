param(
    [string]$ReadmePath = "README.md",
    [string]$RootPath = ".."
)

$ErrorActionPreference = "Stop"

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot $RootPath)).Path
$readmeFullPath = Join-Path $repoRoot $ReadmePath

if (-not (Test-Path -LiteralPath $readmeFullPath)) {
    throw "No se encontró el archivo README en: $readmeFullPath"
}

# --- FUNCIONES AUXILIARES REUTILIZADAS ---
function Get-Json([string]$url) {
    return Invoke-RestMethod -Uri $url -Method Get
}

function Get-RelativePath([string]$fullPath, [string]$basePath) {
    return $fullPath.Substring($basePath.Length + 1)
}

function Get-MarkdownLinkPath([string]$relativePath) {
    $parts = $relativePath -split '[\\/]'
    return (($parts | ForEach-Object { [System.Uri]::EscapeDataString($_) }) -join '/')
}

function Is-Unfinished([string[]]$nonEmptyLines) {
    if (-not $nonEmptyLines) { return $false }
    $tail = ($nonEmptyLines | Select-Object -Last 6) -join "`n"
    if ($tail -match 'Eliminar comentario si el proyecto est') { return $true }
    $last = $nonEmptyLines[-1].Trim()
    if ($last -match '(?i)muy lento|sin terminar|pendiente|todo|wa|tle|mle|re|runtime error|wrong answer|fallo|bug') { return $true }
    return $false
}

function Parse-FolderRound([string]$folderName) {
    if ($folderName -match '^CF R\s+(\d+)') { return @{ Type = 'cf-round'; Number = [int]$matches[1] } }
    if ($folderName -match '^CF Global R\s+(\d+)') { return @{ Type = 'cf-global'; Number = [int]$matches[1] } }
    if ($folderName -match '^Educational CF R\s+(\d+)') { return @{ Type = 'edu'; Number = [int]$matches[1] } }
    if ($folderName -match '^CodeTON R\s+(\d+)') { return @{ Type = 'codeton'; Number = [int]$matches[1] } }
    if ($folderName -match '^Pinely R\s+(\d+)') { return @{ Type = 'pinely'; Number = [int]$matches[1] } }
    if ($folderName -match '^Hello\s+(\d+)') { return @{ Type = 'hello'; Number = [int]$matches[1] } }
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
    return @($token)
}

# --- CARGA DE DATOS DESDE CODEFORCES ---
Write-Output "Cargando lista de problemas de Codeforces para mapear niveles..."
$allProblemsMap = @{}
try {
    $probResponse = Get-Json "https://codeforces.com/api/problemset.problems"
    if ($probResponse.status -eq 'OK') {
        foreach ($p in $probResponse.result.problems) {
            if ($p.contestId -and $p.index) {
                $key = "$([int]$p.contestId)|$([string]$p.index).ToLower()"
                if ($p.rating) { $allProblemsMap[$key] = [int]$p.rating }
            }
        }
    }
} catch {
    Write-Warning "No se pudo conectar con el API de problemas de Codeforces. Los nuevos niveles se calcularán como pendientes."
}

Write-Output "Cargando lista de concursos..."
$contestResponse = Get-Json "https://codeforces.com/api/contest.list?gym=false"
if ($contestResponse.status -ne 'OK') { throw "Error al consultar contest.list" }
$contestList = $contestResponse.result

# --- PROCESAMIENTO DE ARCHIVOS LOCALES ---
$excludeNames = @('Plantilla.cpp', 'test.cpp')
$cppFiles = Get-ChildItem -LiteralPath $repoRoot -Recurse -File -Filter *.cpp |
    Where-Object { $_.FullName -notmatch '\\.vscode\\' -and $_.Name -notin $excludeNames }

$folderContestId = @{}
$folders = $cppFiles | ForEach-Object { Split-Path ($_.FullName.Substring($repoRoot.Length + 1)) -Parent } | Select-Object -Unique
foreach ($f in $folders) {
    $folderContestId[$f] = if ($f -eq 'Randoms') { $null } else { Get-ContestIdFromFolder $f $contestList }
}

$items = foreach ($file in $cppFiles) {
    $raw = [System.IO.File]::ReadAllText($file.FullName)
    $lines = $raw -split "`r?`n"
    $nonEmpty = $lines | Where-Object { $_.Trim() -ne '' }
    
    $relative = Get-RelativePath $file.FullName $repoRoot
    $folder = Split-Path $relative -Parent
    $unfinished = Is-Unfinished $nonEmpty

    # Intentar extraer ContestID e Index
    $contestId = $null
    $index = $null

    # Estrategia 1: Buscar la URL de Codeforces en los comentarios del archivo
    $matchesList = [regex]::Matches($raw, '//\s*https?://codeforces\.com/contest/(\d+)/problem/([^/\s\r\n]+)')

    if ($matchesList.Count -gt 0) {
        $lastMatch = $matchesList[$matchesList.Count - 1]
        $contestId = [int]$lastMatch.Groups[1].Value
        $index = $lastMatch.Groups[2].Value.Trim()
    } else {
        # Estrategia 2: Fallback por nombre de carpeta e índice del archivo
        $contestId = $folderContestId[$folder]
        $candidates = Parse-IndexCandidates $file.Name
        if ($candidates.Count -gt 0) { $index = $candidates[0] }
    }

    # Buscar el Rating/Nivel
    $rating = $null
    if ($contestId -and $index) {
        $ratingKey = "$([int]$contestId)|$([string]$index).ToLower()"
        if ($allProblemsMap.ContainsKey($ratingKey)) {
            $rating = $allProblemsMap[$ratingKey]
        }
    }

    [PSCustomObject]@{
        FileName   = $file.Name
        Folder     = $folder
        Link       = Get-MarkdownLinkPath $relative
        Rating     = $rating
        Unfinished = $unfinished
    }
}

# --- ORDENAR DATOS: Por nivel (los $null/sin nivel van al final) ---
$orderedItems = $items | Sort-Object `
    @{ Expression = { if ($null -eq $_.Rating) { 1 } else { 0 } } }, `
    @{ Expression = 'Rating'; Ascending = $true }, `
    @{ Expression = 'Folder'; Ascending = $true }, `
    @{ Expression = 'FileName'; Ascending = $true }

# --- MODIFICAR EL README ---
$readmeLines = Get-Content -LiteralPath $readmeFullPath -Encoding UTF8
$sectionHeader = '## Problemas por nivel'
$sectionIndexMatch = $readmeLines | Select-String -Pattern '^## Problemas por nivel$' | Select-Object -First 1

$output = New-Object System.Collections.Generic.List[string]

# Conservar todo el contenido previo a esta sección
if ($sectionIndexMatch) {
    $headerIndex = $sectionIndexMatch.LineNumber - 1
    for ($i = 0; $i -lt $headerIndex; $i++) { $output.Add($readmeLines[$i]) | Out-Null }
} else {
    foreach ($line in $readmeLines) { $output.Add($line) | Out-Null }
}

# Asegurar espacio en blanco antes de la tabla
if ($output.Count -gt 0 -and $output[$output.Count - 1] -ne '') { $output.Add('') | Out-Null }

$output.Add($sectionHeader) | Out-Null
$output.Add('') | Out-Null

# Generación de la tabla Markdown
$output.Add('| Problema | Concurso / Carpeta | Nivel (Rating) | Estado |') | Out-Null
$output.Add('| :--- | :--- | :---: | :---: |') | Out-Null

foreach ($entry in $orderedItems) {
    $ratingStr = if ($null -eq $entry.Rating) { 'Pendiente' } else { $entry.Rating }
    $statusStr = if ($entry.Unfinished) { "$([char]0x274C) Sin terminar" } else { "$([char]0x2714) Resuelto" }
    
    $output.Add("| [$($entry.FileName)]($($entry.Link)) | $($entry.Folder) | $ratingStr | $statusStr |") | Out-Null
}

[System.IO.File]::WriteAllLines($readmeFullPath, $output, (New-Object System.Text.UTF8Encoding($true)))

Write-Output "README actualizado: Tabla de posiciones por dificultad generada al final."
Write-Output "Total de problemas indexados en la tabla: $($items.Count)"