#!/bin/bash

echo "========================================"
echo "   Compilando Josephus Visualization"
echo "========================================"

# Crear directorio build si no existe
mkdir -p build
cd build

# Configurar con CMake
echo "Configurando proyecto..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Compilar
echo "Compilando..."
cmake --build .

# Verificar si se compiló correctamente
if [ -f "bin/JosephusVisualization" ]; then
    echo ""
    echo "========================================"
    echo "    Compilación exitosa!"
    echo "========================================"
    echo ""
    echo "Ejecutable creado en: build/bin/JosephusVisualization"
    echo ""
    echo "¿Ejecutar ahora? (y/n)"
    read -r response
    if [[ "$response" =~ ^[Yy]$ ]]; then
        ./bin/JosephusVisualization
    fi
else
    echo ""
    echo "========================================"
    echo "    Error en la compilación"
    echo "========================================"
    echo ""
    echo "Verifica que SFML esté instalado correctamente."
    echo "Consulta el README.md para instrucciones."
    echo ""
    echo "En Ubuntu/Debian: sudo apt install libsfml-dev"
    echo "En Arch Linux: sudo pacman -S sfml"
    echo "En macOS: brew install sfml"
fi

cd ..