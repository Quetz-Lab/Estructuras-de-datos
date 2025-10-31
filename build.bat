@echo off
echo ========================================
echo    Compilando Josephus Visualization
echo ========================================

REM Crear directorio build si no existe
if not exist build mkdir build
cd build

REM Configurar con CMake
echo Configurando proyecto...
cmake .. -DCMAKE_BUILD_TYPE=Release

REM Compilar
echo Compilando...
cmake --build . --config Release

REM Verificar si se compiló correctamente
if exist bin\JosephusVisualization.exe (
    echo.
    echo ========================================
    echo    Compilacion exitosa!
    echo ========================================
    echo.
    echo Ejecutable creado en: build\bin\JosephusVisualization.exe
    echo.
    echo Presiona cualquier tecla para ejecutar...
    pause >nul
    bin\JosephusVisualization.exe
) else (
    echo.
    echo ========================================
    echo    Error en la compilacion
    echo ========================================
    echo.
    echo Verifica que SFML este instalado correctamente.
    echo Consulta el README.md para instrucciones.
    pause
)

cd ..