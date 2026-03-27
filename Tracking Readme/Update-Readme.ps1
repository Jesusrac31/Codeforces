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

function Get-RelativePath([string]$fullPath, [string]$basePath) {
    return $fullPath.Substring($basePath.Length + 1)
}

function Get-MarkdownLinkPath([string]$relativePath) {
    $parts = $relativePath -split '[\\/]'
    return (($parts | ForEach-Object { [System.Uri]::EscapeDataString($_) }) -join '/')
}

function Is-Unfinished([string[]]$nonEmptyLines) {
    if (-not $nonEmptyLines) {
        return $false
    }

    $tail = ($nonEmptyLines | Select-Object -Last 6) -join "`n"
    if ($tail -match 'Eliminar comentario si el proyecto est') {
        return $true
    }

    $last = $nonEmptyLines[-1].Trim()
    if ($last -match '(?i)muy lento|sin terminar|pendiente|todo|wa|tle|mle|re|runtime error|wrong answer|fallo|bug') {
        return $true
    }

    return $false
}

function Parse-FolderDate([string]$folderName) {
    $months = @{
        'ene' = 1; 'feb' = 2; 'mar' = 3; 'abr' = 4; 'may' = 5; 'jun' = 6
        'jul' = 7; 'ago' = 8; 'sep' = 9; 'oct' = 10; 'nov' = 11; 'dic' = 12
    }

    if ($folderName -match '(\d{1,2})-([A-Za-z]{3})-(\d{2})') {
        $d = [int]$matches[1]
        $mKey = $matches[2].ToLower()
        $yy = [int]$matches[3]

        if ($months.ContainsKey($mKey)) {
            $y = 2000 + $yy
            $m = $months[$mKey]
            $safeDay = [Math]::Max(1, [Math]::Min($d, 28))

            try {
                return Get-Date -Year $y -Month $m -Day $safeDay -Hour 0 -Minute 0 -Second 0
            } catch {
                return Get-Date -Year $y -Month $m -Day 1 -Hour 0 -Minute 0 -Second 0
            }
        }
    }

    return Get-Date '1900-01-01'
}

$excludeNames = @('Plantilla.cpp', 'test.cpp')
$cppFiles = Get-ChildItem -LiteralPath $repoRoot -Recurse -File -Filter *.cpp |
    Where-Object {
        $_.FullName -notmatch '\\.vscode\\' -and $_.Name -notin $excludeNames
    }

$items = foreach ($file in $cppFiles) {
    $lines = Get-Content -LiteralPath $file.FullName
    $nonEmpty = $lines | Where-Object { $_.Trim() -ne '' }
    $relative = Get-RelativePath $file.FullName $repoRoot
    $folder = Split-Path $relative -Parent

    [PSCustomObject]@{
        Folder = $folder
        FileName = $file.Name
        Link = Get-MarkdownLinkPath $relative
        Unfinished = Is-Unfinished $nonEmpty
    }
}

$groupedRaw = $items | Group-Object Folder
$randomGroup = $groupedRaw | Where-Object { $_.Name -eq 'Randoms' }

$orderedGroups = $groupedRaw |
    Where-Object { $_.Name -ne 'Randoms' } |
    ForEach-Object {
        [PSCustomObject]@{
            Name = $_.Name
            Group = $_.Group
            SortDate = Parse-FolderDate $_.Name
        }
    } |
    Sort-Object @{ Expression = 'SortDate'; Descending = $true }, @{ Expression = 'Name'; Descending = $false }

if ($randomGroup) {
    $orderedGroups += [PSCustomObject]@{
        Name = $randomGroup.Name
        Group = $randomGroup.Group
        SortDate = Get-Date '1900-01-01'
    }
}

$readmeLines = Get-Content -LiteralPath $readmeFullPath -Encoding UTF8
$sectionHeader = '## Problemas por concurso/carpeta'
$sectionIndexMatch = $readmeLines | Select-String -Pattern '^## Problemas por concurso/carpeta$' | Select-Object -First 1

$prefix = New-Object System.Collections.Generic.List[string]
if ($sectionIndexMatch) {
    $headerIndex = $sectionIndexMatch.LineNumber - 1
    for ($i = 0; $i -lt $headerIndex; $i++) {
        $prefix.Add($readmeLines[$i]) | Out-Null
    }
} else {
    foreach ($line in $readmeLines) {
        $prefix.Add($line) | Out-Null
    }
    if ($prefix.Count -gt 0 -and $prefix[$prefix.Count - 1] -ne '') {
        $prefix.Add('') | Out-Null
    }
}

$output = New-Object System.Collections.Generic.List[string]
foreach ($line in $prefix) {
    $output.Add($line) | Out-Null
}

if ($output.Count -gt 0 -and $output[$output.Count - 1] -ne '') {
    $output.Add('') | Out-Null
}

$output.Add($sectionHeader) | Out-Null
$output.Add('') | Out-Null

foreach ($group in $orderedGroups) {
    $output.Add("### $($group.Name)") | Out-Null
    $output.Add('') | Out-Null

    $sortedFiles = $group.Group | Sort-Object FileName
    foreach ($entry in $sortedFiles) {
        $suffix = if ($entry.Unfinished) { ' (sin terminar)' } else { '' }
        $output.Add("- [$($entry.FileName)]($($entry.Link))$suffix") | Out-Null
    }

    $output.Add('') | Out-Null
}

[System.IO.File]::WriteAllLines($readmeFullPath, $output, (New-Object System.Text.UTF8Encoding($true)))

Write-Output "README actualizado: seccion de problemas regenerada y ordenada."
Write-Output "Concursos/carpetas: $($orderedGroups.Count)"
Write-Output "Problemas listados: $($items.Count)"