g++ -DDEBUG -std=c++17 -O2 -o main.exe %1
@echo off
set start=%time%
.\main.exe < input.in > output.out 
timeout /t 2 >nul 
set end=%time%

:: Extraer partes del tiempo (HH:MM:SS,CC)
set "start_h=%start:~0,2%"
set "start_m=%start:~3,2%"
set "start_s=%start:~6,2%"
set "start_c=%start:~9,2%"

set "end_h=%end:~0,2%"
set "end_m=%end:~3,2%"
set "end_s=%end:~6,2%"
set "end_c=%end:~9,2%"
:: Convertir todo a centisegundos para restar fácilmente
set /a "start_total=(%start_h%*360000)+(%start_m%*6000)+(%start_s%*100)+%start_c%"
set /a "end_total=(%end_h%*360000)+(%end_m%*6000)+(%end_s%*100)+%end_c%"
set /a "diff=end_total-start_total"

echo.
echo ------------------------------
echo Inicio: %start%
echo Fin:    %end%
echo Duracion: %diff% centisegundos
echo ------------------------------
endlocal