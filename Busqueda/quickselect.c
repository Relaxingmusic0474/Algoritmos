#include <stdio.h>

void swap(int *a, int *b);
int partition(int arr[], int low, int high);
int quickselect(int arr[], int low, int high, int k); // Nueva firma: recibe k (índice buscado)

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];

    printf("El pivote es %d\n", pivot);

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int quickselect(int arr[], int low, int high, int k) { // Busca el k-ésimo elemento más pequeño (índice 0-based)

    if (k < 0 || k > high) {
        printf("Índice fuera de rango\n");
        return -1;  // Valor de error
    }

    int p = partition(arr, low, high);                 // Ubica el pivote en su posición final


    if (p == k) {           // Caso base: el pivote ya es el k-ésimo elemento
        return arr[p];      // Retorna el valor encontrado
    } else if (k < p) {     // El k-ésimo está en la mitad izquierda
        return quickselect(arr, low, p - 1, k);     // Recursión solo por la izquierda
    } else {                // El k-ésimo está en la mitad derecha
        return quickselect(arr, p + 1, high, k);    // Recursión solo por la derecha
    }
}

int main() {
    int arr[] = {7, 2, 1, 6, 8, 5, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 5;                                              // Índice buscado (0-based): k=2 → 3er elemento más pequeño
    int resultado = quickselect(arr, 0, n - 1, k);         // Llama a quickselect sobre el arreglo completo
    printf("\nEl elemento %d-ésimo más pequeño es: %d\n", k + 1, resultado); // Muestra el resultado final
    return 0;
}