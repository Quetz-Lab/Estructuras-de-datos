cmake_minimum_required(VERSION 3.16)
project(JosephusVisualization)

# Configurar estándar C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar SFML
find_package(SFML 3 QUIET COMPONENTS graphics window system)

# Si no encuentra SFML 3, intentar con SFML 2
if(NOT SFML_FOUND)
    find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
endif()

# Crear el ejecutable
add_executable(JosephusVisualization 
    "Estructuras de datos/main.cpp"
)

# Enlazar librerías SFML
target_link_libraries(JosephusVisualization 
    sfml-graphics 
    sfml-window 
    sfml-system
)

# Configuración específica para Windows
if(WIN32)
    # Copiar DLLs de SFML al directorio de salida en Windows
    if(SFML_FOUND)
        # Para SFML 3
        set(SFML_DLL_DIR "${SFML_ROOT}/bin")
    else()
        # Para SFML 2
        set(SFML_DLL_DIR "${SFML_ROOT}/bin")
    endif()
    
    # Buscar y copiar DLLs necesarias
    file(GLOB SFML_DLLS "${SFML_DLL_DIR}/*.dll")
    foreach(dll ${SFML_DLLS})
        add_custom_command(TARGET JosephusVisualization POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${dll} $<TARGET_FILE_DIR:JosephusVisualization>)
    endforeach()
endif()

# Configuración para diferentes tipos de build
set_target_properties(JosephusVisualization PROPERTIES
    DEBUG_POSTFIX "_d"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Mostrar información útil
message(STATUS "Configurando Josephus Visualization")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
if(SFML_FOUND)
    message(STATUS "SFML encontrado: ${SFML_VERSION}")
else()
    message(WARNING "SFML no encontrado. Asegúrate de tenerlo instalado.")
endif()