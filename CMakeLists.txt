# Versión de CMake
cmake_minimum_required(VERSION 3.10)

# Quiz 3_Manejo de encriptados
project(Quiz3_Manejo_Estructuras_Encriptadas 
    VERSION 1.0
    DESCRIPTION "Programa para manipular estructuras encriptadas - IE0117"
    LANGUAGES C
)

# Configuración de C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra")

# 1. Copiar archivos .bin al directorio de construcción
configure_file(
    ${CMAKE_SOURCE_DIR}/src/sensor_encrypted.bin
    ${CMAKE_BINARY_DIR}/sensor_encrypted.bin
    COPYONLY
)

# 2. Asegurar que los archivos binarios estén disponibles
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/sensor_updated_encrypted.bin
    DEPENDS quiz3
    COMMENT "Generando archivo de salida encriptado"
)

# --------------------------------------------------
# Ejecutable principal
# --------------------------------------------------
add_executable(quiz3 src/main.c)

# Mensaje de confirmación
message(STATUS "\n✅ Configuración lista para:")
message(STATUS "   - Ejecutable: quiz3")
message(STATUS "   - Binarios: sensor_*.bin\n")
