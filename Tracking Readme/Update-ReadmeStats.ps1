param(
    [string]$ReadmePath = "README.md",
    [string]$RootPath = ".."
)

$ErrorActionPreference = "Stop"

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot $RootPath)).Path
$readmeFullPath = Join-Path $repoRoot $ReadmePath

if (-not (Test-Path -LiteralPath $readmeFullPath)) {
    throw "No se encontro el archivo README en: $readmeFullPath"
}

$lines = Get-Content -LiteralPath $readmeFullPath -Encoding UTF8

$total = 0
$unfinished = 0

foreach ($line in $lines) {
    if ($line -match '^- \[.+\]\(.+\)( \(sin terminar\))?$') {
        $total++
        if ($line -match '\(sin terminar\)\s*$') {
            $unfinished++
        }
    }
}

$solved = $total - $unfinished
$percentage = if ($total -gt 0) {
    [Math]::Round((100.0 * $solved) / $total, 2)
} else {
    0
}

$resolutionLabel = "Porcentaje de resoluci$([char]0x00F3)n"

$resumenHeaderMatch = $lines | Select-String -Pattern '^## Resumen$' | Select-Object -First 1

if (-not $resumenHeaderMatch) {
    throw "No se encontro la seccion '## Resumen' en el README."
}

$resumenStart = $resumenHeaderMatch.LineNumber - 1
$nextHeaderMatch = $lines | Select-String -Pattern '^## ' | Where-Object { $_.LineNumber -gt ($resumenStart + 1) } | Select-Object -First 1

if ($nextHeaderMatch) {
    $resumenEndExclusive = $nextHeaderMatch.LineNumber - 1
} else {
    $resumenEndExclusive = $lines.Count
}

$newResumenBlock = @(
    '## Resumen',
    '',
    "- Problemas intentados: **$total**",
    "- Problemas resueltos: **$solved**",
    "- Problemas sin terminar: **$unfinished**",
    "- ${resolutionLabel}: **$percentage%**",
    ''
)

$output = New-Object System.Collections.Generic.List[string]

for ($i = 0; $i -lt $resumenStart; $i++) {
    $output.Add($lines[$i]) | Out-Null
}

foreach ($line in $newResumenBlock) {
    $output.Add($line) | Out-Null
}

for ($i = $resumenEndExclusive; $i -lt $lines.Count; $i++) {
    $output.Add($lines[$i]) | Out-Null
}

[System.IO.File]::WriteAllLines($readmeFullPath, $output, (New-Object System.Text.UTF8Encoding($true)))

Write-Output "Resumen actualizado."
Write-Output "Intentados=$total | Resueltos=$solved | Sin terminar=$unfinished | Porcentaje=$percentage%"