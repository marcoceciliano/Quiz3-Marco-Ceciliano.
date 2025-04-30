# Quiz 3 - Manejo de Estructuras Encriptadas  
## Objetivo  
Programa en C que:  
- En primera instancia lee `sensor_encrypted.bin` (con una estructura de Sensor encriptada con XOR)  
- Seguidamente añde un campo con `temperatura` (30.0)  
- Luego de esto lo guarda en `sensor_updated_encrypted.bin`
  
## El proyecto se encuentra estructurado de la siguiente manera  
quiz3/
├── CMakeLists.txt
├── README.md
└── src/
├── main.c
├── sensor_encrypted.bin
└── sensor_updated_encrypted.bin

## Compilación  
### Método 1: CMake   
```bash
mkdir build && cd build  # Crea y entra a la carpeta de compilación
cmake ..                 # Genera archivos Makefile usando CMakeLists.txt
make                     # Compila el programa
./quiz3                  # Ejecuta el programa

### Método 2: GCC directo 
gcc src/main.c -o quiz3 && ./quiz3

## Resultados esperados 
Datos originales:
ID: 1 | Valor: 25.50 | Timestamp: 2024-05-20 14:30:00

Datos actualizados:
ID: 1 | Valor: 25.50 | Timestamp: 2024-05-20 14:30:00 | Temperatura: 30.0


