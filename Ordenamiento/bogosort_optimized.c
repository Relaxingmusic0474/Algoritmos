#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 1000000

#define MIN_VALUE -3000000
#define MAX_VALUE 4000000

// Estructura para representar una cadena (sub-arreglo) ya ordenada
typedef struct {
    int* data;
    int size;
} Block;

// Función auxiliar para mezclar un arreglo (Fisher-Yates Shuffle)
void shuffle(int array[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Función estándar para fusionar dos bloques ordenados (Merge)
Block merge_blocks(Block a, Block b) {
    Block result;
    result.size = a.size + b.size;
    result.data = (int*)malloc(result.size * sizeof(int));

    int i = 0, j = 0, k = 0;
    while (i < a.size && j < b.size) {
        if (a.data[i] <= b.data[j]) {
            result.data[k++] = a.data[i++];
        } else {
            result.data[k++] = b.data[j++];
        }
    }
    while (i < a.size) result.data[k++] = a.data[i++];
    while (j < b.size) result.data[k++] = b.data[j++];

    return result;
}

// Escanea el arreglo de elementos desordenados para extraer cadenas de 2 o más elementos
int identify_chains(int unassigned[], int unassigned_size, Block blocks[], int* block_count) {
    if (unassigned_size == 0) return 0;

    bool* used = (bool*)calloc(unassigned_size, sizeof(bool));
    int remaining_count = 0;

    for (int i = 0; i < unassigned_size; i++) {
        if (used[i]) continue;

        // Intentar formar una cadena a partir de la posición i
        int start = i;
        int end = i;

        // Buscamos elementos consecutivos que mantengan el orden
        while (end + 1 < unassigned_size && !used[end + 1] && unassigned[end] <= unassigned[end + 1]) {
            end++;
        }

        int chain_length = end - start + 1;

        if (chain_length >= 2) {
            // Guardamos la cadena como un bloque ordenado
            blocks[*block_count].size = chain_length;
            blocks[*block_count].data = (int*)malloc(chain_length * sizeof(int));
            int k = 0;
            for (int j = start; j <= end; j++) {
                blocks[*block_count].data[k++] = unassigned[j];
                used[j] = true;
            }
            (*block_count)++;
        }
    }

    // Recolectamos los elementos que se quedaron huérfanos (no entraron en ninguna cadena)
    int temp_idx = 0;
    for (int i = 0; i < unassigned_size; i++) {
        if (!used[i]) {
            unassigned[temp_idx++] = unassigned[i];
            remaining_count++;
        }
    }

    free(used);
    return remaining_count; // Devuelve cuántos elementos siguen desordenados
}

void bogosort_optimized(int array[], int size) {
    if (size <= 1) return;

    // Reservas de memoria máximas posibles
    Block* blocks = (Block*)malloc(size * sizeof(Block));
    int block_count = 0;

    int* unassigned = (int*)malloc(size * sizeof(int));
    int unassigned_size = size;
    
    // Copiar el arreglo original al de trabajo desordenado
    for (int i = 0; i < size; i++) unassigned[i] = array[i];

    // --- FASE 1: BOGOSORT ADAPTATIVO POR BLOQUES ---
    while (unassigned_size > 0) {
        // Pasar el filtro para identificar cadenas ordenadas de 2 o más elementos
        int prev_size;
        do {
            prev_size = unassigned_size;
            unassigned_size = identify_chains(unassigned, unassigned_size, blocks, &block_count);
        } while (unassigned_size < prev_size && unassigned_size > 1); 
        // Se repite la pasada si en la anterior logramos reducir los elementos sueltos

        // Si quedan al menos 2 elementos huérfanos y ya no forman cadenas, los mezclamos
        if (unassigned_size >= 2) {
            shuffle(unassigned, unassigned_size);
        } 
        // Si queda exactamente 1 elemento huérfano, automáticamente es una cadena de tamaño 1
        else if (unassigned_size == 1) {
            blocks[block_count].size = 1;
            blocks[block_count].data = (int*)malloc(sizeof(int));
            blocks[block_count].data[0] = unassigned[0];
            block_count++;
            unassigned_size = 0;
        }
    }

    // --- FASE 2: MERGE DE LOS BLOQUES ---
    // Vamos fusionando los bloques de dos en dos hasta que solo quede uno
    while (block_count > 1) {
        int new_block_count = 0;
        for (int i = 0; i < block_count; i += 2) {
            if (i + 1 < block_count) {
                Block merged = merge_blocks(blocks[i], blocks[i+1]);
                free(blocks[i].data);
                free(blocks[i+1].data);
                blocks[new_block_count++] = merged;
            } else {
                // Si queda un bloque impar, pasa a la siguiente ronda directamente
                blocks[new_block_count++] = blocks[i];
            }
        }
        block_count = new_block_count;
    }

    // Copiar el resultado final ordenado de vuelta al arreglo original
    for (int i = 0; i < size; i++) {
        array[i] = blocks[0].data[i];
    }

    // Limpieza final de memoria
    free(blocks[0].data);
    free(blocks);
    free(unassigned);
}

int main() {
    srand(time(NULL));
    int array[SIZE];

    for (int i=0; i<SIZE; i++) {
        array[i] = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
    }

    bogosort_optimized(array, SIZE);
    return 0;
}