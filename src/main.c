#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float valor;
    char timestamp[20];
} Sensor;

typedef struct {
    int id;
    float valor;
    char timestamp[20];
    float temperatura;
} SensorUpdated;

void encrypt_file(const char *input_filename, const char *output_filename, unsigned char key) {
    FILE *input = fopen(input_filename, "rb");
    FILE *output = fopen(output_filename, "wb");
    if (!input || !output) {
        perror("Error al abrir archivos");
        exit(1);
    }

    int c;
    while ((c = fgetc(input)) != EOF) {
        fputc(c ^ key, output);
    }

    fclose(input);
    fclose(output);
}

int main() {
    const unsigned char key = 0xAB;
    
    // Paso 1: Leer archivo encriptado original
    const char *input_file = "sensor_encrypted.bin";
    const char *temp_file = "temp.bin";
    
    // Desencriptar a archivo temporal
    encrypt_file(input_file, temp_file, key);
    
    // Leer estructura original
    FILE *file = fopen(temp_file, "rb");
    if (!file) {
        perror("Error al abrir archivo temporal");
        remove(temp_file);
        return 1;
    }
    
    Sensor sensor;
    if (fread(&sensor, sizeof(Sensor), 1, file) != 1) {
        perror("Error al leer sensor");
        fclose(file);
        remove(temp_file);
        return 1;
    }
    fclose(file);
    
    // Mostrar valores originales
    printf("Datos originales:\n");
    printf("ID: %d\n", sensor.id);
    printf("Valor: %.2f\n", sensor.valor);
    printf("Timestamp: %s\n", sensor.timestamp);
    
    // Paso 2: Añadir temperatura
    SensorUpdated updated = {
        .id = sensor.id,
        .valor = sensor.valor,
        .temperatura = 30.0f  // Valor ejemplo del enunciado
    };
    strncpy(updated.timestamp, sensor.timestamp, 20);
    
    // Paso 3: Guardar estructura actualizada
    const char *updated_temp = "temp_updated.bin";
    const char *output_file = "sensor_updated_encrypted.bin";
    
    FILE *out = fopen(updated_temp, "wb");
    if (!out) {
        perror("Error al crear archivo temporal");
        remove(temp_file);
        return 1;
    }
    
    fwrite(&updated, sizeof(SensorUpdated), 1, out);
    fclose(out);
    
    // Encriptar archivo actualizado
    encrypt_file(updated_temp, output_file, key);
    
    // Paso 4: Verificación
    printf("\nVerificando archivo actualizado...\n");
    encrypt_file(output_file, updated_temp, key);
    
    FILE *verify = fopen(updated_temp, "rb");
    if (!verify) {
        perror("Error al verificar archivo");
        remove(updated_temp);
        remove(temp_file);
        return 1;
    }
    
    SensorUpdated verified;
    if (fread(&verified, sizeof(SensorUpdated), 1, verify) != 1) {
        perror("Error al leer archivo verificado");
        fclose(verify);
        remove(updated_temp);
        remove(temp_file);
        return 1;
    }
    fclose(verify);
    
    printf("Datos verificados:\n");
    printf("ID: %d\n", verified.id);
    printf("Valor: %.2f\n", verified.valor);
    printf("Timestamp: %s\n", verified.timestamp);
    printf("Temperatura: %.1f\n", verified.temperatura);
    
    // Limpieza
    remove(temp_file);
    remove(updated_temp);
    
    return 0;
    }

    
