#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define SIZE 1000000
#define LOW -100000
#define HIGH 100000
#define REPETITIONS 3

typedef unsigned int Natural;
typedef int Index;

static int array[SIZE];
static int backup_array[SIZE];

void swap(int* a, int* b);
void generate_array(int array[], Natural size, int low, int high);
void copy_array(int source[], int dest[], Natural size);
void insertion_sort(int array[], Natural size);
void semi_shell_sort(int array[], Natural size);
void semi_shell_sort_v2(int array[], Natural size);
void shell_sort(int array[], Natural size);

int main()
{
    clock_t start, end;
    double exec_time_semishell, average_time_semishell = 0.0f;
    double exec_time_semishell_v2, average_time_semishell_v2 = 0.0f;
    double exec_time_shell, average_time_shell = 0.0f;

    srand(time(NULL));

    FILE* sorting_algorithm_cpu_times_file = fopen("part_ii_sorting_algoritm_cpu_times_file.csv", "a+");

    if (!sorting_algorithm_cpu_times_file) {
        perror("File couldn't be opened.");
        return 1;
    }

    //fprintf(sorting_algorithm_cpu_times_file, "%s,%s,%s,%s\n", "Nro_datos", "Tiempo_semishell(s)", "Tiempo_semishell_v2(s)", "Tiempo_shell(s)");

    for (Natural i=0; i<REPETITIONS; i++)
    {
        // Generamos los datos aleatorios directamente en nuestro arreglo base
        generate_array(backup_array, SIZE, LOW, HIGH);
    
        // --- PRUEBA SHELL SORT ---
        copy_array(backup_array, array, SIZE); // Restauramos el desorden original
        start = clock();
        shell_sort(array, SIZE);
        end = clock();
        exec_time_shell = (double) (end - start) / CLOCKS_PER_SEC;

        // --- PRUEBA SEMI SHELL SORT V2 (SELECTION) ---
        copy_array(backup_array, array, SIZE); // Restauramos el desorden original
        start = clock();
        semi_shell_sort_v2(array, SIZE);
        end = clock();
        exec_time_semishell_v2 = (double) (end - start) / CLOCKS_PER_SEC;

        // --- PRUEBA SEMI SHELL SORT ---
        copy_array(backup_array, array, SIZE); // Restauramos el desorden original
        start = clock();
        semi_shell_sort(array, SIZE);
        end = clock();
        exec_time_semishell = (double) (end - start) / CLOCKS_PER_SEC;

        average_time_shell += exec_time_shell;
        average_time_semishell_v2 += exec_time_semishell_v2;
        average_time_semishell += exec_time_semishell;
    }

    average_time_shell = average_time_shell / REPETITIONS;
    average_time_semishell_v2 = average_time_semishell_v2 / REPETITIONS;
    average_time_semishell = average_time_semishell / REPETITIONS;

    // Guardar en el CSV con especificador %u para variables de tipo 'unsigned int' (Natural)
    fprintf(sorting_algorithm_cpu_times_file, "%u,%.8f,%.8f,%.8f\n", SIZE, average_time_semishell, average_time_semishell_v2, average_time_shell);
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

void semi_shell_sort_v2(int array[], Natural size) 
{
    Natural gap = size / 2;

    if (size & 1) {
        gap++;
    }

    while (gap > 1) 
    {
        for (Index i=0; i<gap; i++) {

            Index min_idx = i;

            for (Index idx=i+gap; idx<size; idx+=gap) {
                if (array[idx] < array[min_idx]) {
                    min_idx = idx;
                }
            }

            if (min_idx != i) {
                swap(&array[min_idx], &array[i]);
            }
        }

        gap = gap/2;
    }

    insertion_sort(array, size);
}

void shell_sort(int array[], Natural size) 
{
    // Ej: array = {5, 10, 8, 13, 2, 11, 7, 0};
    Natural gap = size / 2;   // size = 8, gap = 4;

    if (size & 1) {
        gap++;
    }

    while (gap > 0) // Si gap = 4;
    {
        for (Index i=gap; i<size; i++) {  // i: 4->7
            int key = array[i];  // i=4 -> key = array[4] = 2
            Index j = i; // j=4

            while (j>=gap && array[j-gap]>key) {  // j=4 -> 4>=4 && array[4-4]=5 > key=2
                array[j] = array[j-gap];  // j=4 -> array[4] = array[0] = 5
                j -= gap;  // j=4 -> j=0
            }

            array[j] = key;  // array[0] = 2
        }

        gap = gap/2;
    }
}