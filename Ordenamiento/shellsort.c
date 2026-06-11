#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "time.h"

#define SIZE 100000
#define LOW -20
#define HIGH 50
#define REPETITIONS 10

typedef unsigned int Natural;
typedef int Index;

// Mover los arreglos fuera del main evita el Stack Overflow con tamaños grandes
static int array[SIZE];
static int backup_array[SIZE];

void swap(int* a, int* b);
void generate_array(int array[], Natural size, int low, int high);
void copy_array(int source[], int dest[], Natural size);
void bubble_sort(int array[], Natural size);
void selection_sort(int array[], Natural size);
void insertion_sort(int array[], Natural size);
void semi_shell_sort(int array[], Natural size);

int main() 
{
    clock_t start, end;
    double exec_time_bubble, average_time_bubble = 0.0f;
    double exec_time_selection, average_time_selection = 0.0f;
    double exec_time_insertion, average_time_insertion = 0.0f;
    double exec_time_semishell, average_time_semishell = 0.0f;

    srand(time(NULL));

    FILE* sorting_algorithm_cpu_times_file = fopen("sorting_algoritm_cpu_times_file.csv", "a+");

    if (!sorting_algorithm_cpu_times_file) {
        perror("File couldn't be opened.");
        return 1;
    }

    //fprintf(sorting_algorithm_cpu_times_file, "%s,%s,%s,%s,%s\n", "Nro_datos", "Tiempo_burbuja(s)", "Tiempo_selección(s)", "Tiempo_inserción(s)", "Tiempo_semishell(s)");

    for (Natural i=0; i<REPETITIONS; i++)
    {
        // Generamos los datos aleatorios directamente en nuestro arreglo base
        generate_array(backup_array, SIZE, LOW, HIGH);
    
        // --- PRUEBA BUBBLE SORT ---
        copy_array(backup_array, array, SIZE); // Restauramos el desorden original
        start = clock();
        bubble_sort(array, SIZE);
        end = clock();
        exec_time_bubble = (double) (end - start) / CLOCKS_PER_SEC;

        // --- PRUEBA SELECTION SORT ---
        copy_array(backup_array, array, SIZE); // Restauramos el desorden original
        start = clock();
        selection_sort(array, SIZE);
        end = clock();
        exec_time_selection = (double) (end - start) / CLOCKS_PER_SEC;

        // --- PRUEBA INSERTION SORT ---
        copy_array(backup_array, array, SIZE); // Restauramos el desorden original
        start = clock();
        insertion_sort(array, SIZE);
        end = clock();
        exec_time_insertion = (double) (end - start) / CLOCKS_PER_SEC;

        // --- PRUEBA SEMI SHELL SORT ---
        copy_array(backup_array, array, SIZE); // Restauramos el desorden original
        start = clock();
        semi_shell_sort(array, SIZE);
        end = clock();
        exec_time_semishell = (double) (end - start) / CLOCKS_PER_SEC;

        average_time_bubble += exec_time_bubble;
        average_time_selection += exec_time_selection;
        average_time_insertion += exec_time_insertion;
        average_time_semishell += exec_time_semishell;
    }

    average_time_bubble = average_time_bubble / REPETITIONS;
    average_time_selection = average_time_selection / REPETITIONS;
    average_time_insertion = average_time_insertion / REPETITIONS;
    average_time_semishell = average_time_semishell / REPETITIONS;

    // Guardar en el CSV con especificador %u para variables de tipo 'unsigned int' (Natural)
    fprintf(sorting_algorithm_cpu_times_file, "%u,%.8f,%.8f,%.8f,%.8f\n", SIZE, average_time_bubble, average_time_selection, average_time_insertion, average_time_semishell);
    fclose(sorting_algorithm_cpu_times_file);

    printf("Pruebas finalizadas con éxito para %u elementos.\n", SIZE);
    return 0;
}

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Cambiada a tipo 'void' ya que modifica directamente el arreglo por referencia
void generate_array(int array[], Natural size, int low, int high) {
    for (Index i=0; i<size; i++) {
        array[i] = (rand() % (high-low+1)) + low;
    }
}

// Copia eficiente de bloques de memoria
void copy_array(int source[], int dest[], Natural size) {
    for (Index i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

void bubble_sort(int array[], Natural size)
{
    Natural j = size-1;
    
    while (j > 0) {    
        bool swapped = false; // Debe resetearse a false en cada pasada completa
        for (Index i=0; i<j; i++) {
            if (array[i] > array[i+1]) {
                swap(&array[i], &array[i+1]);
                swapped = true;
            }
        }

        j--;

        if (!swapped) {
            break;
        }
    }
}

void selection_sort(int array[], Natural size)
{
    for (Index i=0; i<size-1; i++) {
        Index min_idx = i;
        
        for (Index j=i+1; j<size; j++) {
            if (array[j] < array[min_idx]) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            swap(&array[i], &array[min_idx]);
        }
    }
}

void insertion_sort(int array[], Natural size)
{
    Index i, j;
    int key;

    for (i = 1; i < size; i++) {
        key = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void semi_shell_sort(int array[], Natural size) 
{
    Natural gap = size / 2;

    if (size & 1) {
        gap++;
    }

    while (gap > 1) 
    {
        for (Index i=0; i<gap; i++) {
            Index idx = i+gap;

            if (idx >= size) {
                break;
            }

            if (array[i] > array[idx]) {
                swap(&array[i], &array[idx]);
            }
        }

        gap = gap/2;
    }

    insertion_sort(array, size);
}
