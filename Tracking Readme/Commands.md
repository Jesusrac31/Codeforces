# Tracking Readme - Comandos

Estos son los comandos principales para mantener el estado de los problemas y el README.

## 1. Completar comentarios de estado en archivos

Se encarga de revisar los archivos de problemas y anadir el comentario final cuando falte.

```powershell
powershell -ExecutionPolicy Bypass -File ".\Tracking Readme\Backfill-StatusComments.ps1"
```

## 2. Regenerar listado de problemas en el README

Actualiza la seccion de problemas del README (orden cronologico y deteccion de nuevos archivos).

```powershell
powershell -ExecutionPolicy Bypass -File ".\Tracking Readme\Update-Readme.ps1"
```

## 3. Recalcular resumen de estadisticas

Recuenta intentados/resueltos/sin terminar y actualiza el bloque de resumen del README.

```powershell
powershell -ExecutionPolicy Bypass -File ".\Tracking Readme\Update-ReadmeStats.ps1"
```

## Flujo completo recomendado

Ejecuta los tres comandos en este orden para dejar todo actualizado:

```powershell
powershell -ExecutionPolicy Bypass -File ".\Tracking Readme\Backfill-StatusComments.ps1"; powershell -ExecutionPolicy Bypass -File ".\Tracking Readme\Update-Readme.ps1"; powershell -ExecutionPolicy Bypass -File ".\Tracking Readme\Update-ReadmeStats.ps1"
```

En cmd:
```cmd
powershell -ExecutionPolicy Bypass -File ".\Tracking Readme\Backfill-StatusComments.ps1" & powershell -ExecutionPolicy Bypass -File ".\Tracking Readme\Update-Readme.ps1" & powershell -ExecutionPolicy Bypass -File ".\Tracking Readme\Update-ReadmeStats.ps1"
```
