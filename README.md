# Visualización del Problema de Josephus

Una implementación interactiva del problema de Josephus usando SFML para la visualización gráfica.

## 🎯 Características

- **Círculo de soldados**: Se crean automáticamente al ingresar el número
- **Cálculo automático**: Muestra el soldado sobreviviente antes de empezar
- **Visualización interactiva**: Presiona 'K' para eliminar soldados uno por uno
- **Línea de ataque**: Muestra visualmente quién ataca a quién
- **Efectos visuales**: Soldados azules (vivos) → rojos (eliminados)

## 🛠️ Requisitos

- C++17 o superior
- SFML 2.5+ o SFML 3.0+
- CMake 3.16+ (recomendado)

## 📦 Instalación de SFML

### Windows
1. **Opción 1 - vcpkg (recomendado):**
   ```bash
   vcpkg install sfml
   ```

2. **Opción 2 - Descarga manual:**
   - Descargar SFML desde https://www.sfml-dev.org/download.php
   - Extraer en `C:\SFML` o similar
   - Configurar variable de entorno `SFML_ROOT`

### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install libsfml-dev cmake build-essential
```

### Linux (Arch)
```bash
sudo pacman -S sfml cmake base-devel
```

### macOS
```bash
brew install sfml cmake
```

## 🚀 Compilación

### Con CMake (recomendado)
```bash
# Crear directorio de build
mkdir build
cd build

# Configurar proyecto
cmake ..

# Compilar
cmake --build .

# Ejecutar
./bin/JosephusVisualization
```

### Con Visual Studio (Windows)
1. Abrir `Estructuras de datos.sln`
2. Compilar y ejecutar (F5)

### Compilación manual
```bash
# Linux/macOS
g++ -std=c++17 "Estructuras de datos/main.cpp" -lsfml-graphics -lsfml-window -lsfml-system -o josephus

# Windows (MinGW)
g++ -std=c++17 "Estructuras de datos/main.cpp" -lsfml-graphics -lsfml-window -lsfml-system -o josephus.exe
```

## 🎮 Uso

1. **Ejecutar el programa**
2. **Ingresar número de soldados** (1-50)
3. **Ver el soldado sobreviviente calculado**
4. **Presionar 'K'** repetidamente para eliminar soldados
5. **Observar la línea de ataque** que conecta atacante con objetivo

## 🎨 Elementos Visuales

- **🔵 Soldados vivos**: Círculos azules con borde blanco
- **🔴 Soldados eliminados**: Círculos rojos con borde negro
- **🟡 Línea de ataque**: Conecta atacante con objetivo (2 segundos)
- **🟡 Atacante**: Borde amarillo grueso (temporal)
- **🔴 Objetivo**: Borde rojo grueso (temporal)

## 🏗️ IDEs Compatibles

### Con CMake:
- **CLion** (JetBrains)
- **Qt Creator**
- **Visual Studio Code** (con extensión CMake)
- **Visual Studio 2019/2022**
- **Code::Blocks** (con CMake)

### Configuración manual:
- **Dev-C++**
- **Code::Blocks**
- **Eclipse CDT**

## 🐛 Solución de Problemas

### "SFML no encontrado"
- Verificar que SFML esté instalado
- Configurar variable `SFML_ROOT` si es necesario
- En Linux: `sudo ldconfig` después de instalar

### "DLLs faltantes" (Windows)
- Las DLLs se copian automáticamente con CMake
- Manualmente: copiar DLLs de `SFML/bin` al directorio del ejecutable

### Errores de compilación
- Verificar C++17 habilitado
- Verificar rutas de include y librerías
- En Linux: instalar paquetes de desarrollo

## 📝 Algoritmo

Implementa el problema clásico de Josephus con k=2:
- Los soldados se eliminan cada 2 posiciones
- Fórmula recursiva: `J(n) = (J(n-1) + k) % n`
- Visualización paso a paso del proceso

## 🎓 Propósito Educativo

Este proyecto demuestra:
- Algoritmos recursivos
- Estructuras de datos circulares
- Programación gráfica con SFML
- Visualización de algoritmos
- Gestión de eventos en tiempo real