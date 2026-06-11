
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

#define SIZE 300000
#define NUM_ARRAYS_WORST_CASE 128
#define MIN_SEARCHES 100000
#define TOTAL_OPERATIONS 1000000000LL
#define SEARCHES (((TOTAL_OPERATIONS / SIZE) >= MIN_SEARCHES) ? (TOTAL_OPERATIONS / SIZE) : MIN_SEARCHES)

#define MIN_VALUE (-5 * SIZE / 4)
#define MAX_JUMP 5

#define MIN_VALUE_WORST_CASE_ARRAY -10
#define MAX_VALUE_WORST_CASE_ARRAY 20

typedef long int Index;
typedef unsigned short Natural;

Index interpolation_search(long array[], int size, long target) 
{
    if (size < 1) {
        return -1;
    }

    if (array[size-1] == array[0]) {
        return (array[0] == target) ? 0 : -1;
    }

    Index supposed_idx = (float) (target - array[0]) / (array[size-1] - array[0]) * (size-1);
    Index start_idx = 0, end_idx = size-1;

    if (supposed_idx < 0 || supposed_idx > size-1) {
        return -1;
    }

    do
    {
        if (array[supposed_idx] == target) {
            return supposed_idx;
        }

        else if (array[supposed_idx] > target) {
            end_idx = supposed_idx - 1;
        }

        else {  // array[supposed_idx] < target
            start_idx = supposed_idx + 1;
        }

        if (start_idx > end_idx) {
            break;
        }

        if (array[end_idx] == array[start_idx]) {
            if (array[start_idx] != target) {
                break;
            }

            return start_idx;
        }

        supposed_idx = start_idx + (float) (target - array[start_idx]) / (array[end_idx] - array[start_idx]) * (end_idx - start_idx);

        if (supposed_idx < start_idx || supposed_idx > end_idx) {
            break;
        } 
    }
    while (start_idx <= end_idx);

    return -1;
}

Index binary_search(long array[], int size, long target) 
{
    if (size < 1) {
        return -1;
    }

    Index start_idx = 0, end_idx = size-1;
    Index mid_idx;
    
    while (start_idx <= end_idx) {
        mid_idx = start_idx + (end_idx - start_idx) / 2;
        
        if (array[mid_idx] == target) {
            return mid_idx;
        }

        else if (array[mid_idx] > target) {
            end_idx = mid_idx - 1;
        }

        else {  // array[mid_idx] < target
            start_idx = mid_idx + 1;
        }
    }

    return -1;
}

Index binary_search_segment_array(long array[], int start_position, int end_position, long target) 
{
    if (start_position > end_position) {
        return -1;
    }

    Index start_idx = start_position, end_idx = end_position;
    Index mid_idx;
    
    while (start_idx <= end_idx) {
        mid_idx = start_idx + (end_idx - start_idx) / 2;
        
        if (array[mid_idx] == target) {
            return mid_idx;
        }

        else if (array[mid_idx] > target) {
            end_idx = mid_idx - 1;
        }

        else {  // array[mid_idx] < target
            start_idx = mid_idx + 1;
        }
    }

    return -1;
}

Index introspective_search(long array[], int size, long target)
{
    if (size < 1) {
        return -1;
    }

    if (array[size-1] == array[0]) {
        return (array[0] == target) ? 0 : -1;
    }

    Index supposed_idx = (float) (target - array[0]) / (array[size-1] - array[0]) * (size-1);
    Index start_idx = 0, end_idx = size-1;

    if (supposed_idx < 0 || supposed_idx > size-1) {
        return -1;
    }

    Natural attempts = 0, max_attempts = log2(size);

    do
    {
        if (array[supposed_idx] == target) {
            return supposed_idx;
        }

        else if (array[supposed_idx] > target) {
            end_idx = supposed_idx - 1;
        }

        else {  // array[supposed_idx] < target
            start_idx = supposed_idx + 1;
        }

        if (start_idx > end_idx) {
            break;
        }

        if (array[end_idx] == array[start_idx]) {
            if (array[start_idx] != target) {
                break;
            }

            return start_idx;
        }

        attempts++;

        supposed_idx = start_idx + (float) (target - array[start_idx]) / (array[end_idx] - array[start_idx]) * (end_idx - start_idx);
    
        if (supposed_idx < start_idx || supposed_idx > end_idx) {
            break;
        } 
    }
    while (start_idx <= end_idx && attempts <= max_attempts);

    return binary_search_segment_array(array, start_idx, end_idx, target);
}

void generate_worst_case_array(long array[], int size)
{
    array[0] = (rand() % (MAX_VALUE_WORST_CASE_ARRAY - MIN_VALUE_WORST_CASE_ARRAY + 1)) + MIN_VALUE_WORST_CASE_ARRAY;

    for (Index i=1; i<size; i++) {
        array[i] = array[i-1] + 1;
    }

    array[size-1] = array[size-2] * (size / 10);
}

int main() 
{
    long* targets = NULL;
    long* array = NULL, **arrays_worst_case = NULL;

    targets = (long *) calloc(SEARCHES, sizeof(long));

    if (!targets) {
        perror("Allocation memory error.");
        return 1;
    }

    array = (long *) calloc(SIZE, sizeof(long));

    if (!array) {
        perror("Allocation memory error.");
        free(targets);
        targets = NULL;
        return 1;
    }

    arrays_worst_case = (long**) calloc(NUM_ARRAYS_WORST_CASE, sizeof(long*));
    
    if (!arrays_worst_case) {
        perror("Allocation memory error.");
        free(targets);
        targets = NULL;
        free(array);
        array = NULL;
        return 1;
    }

    for (Index i=0; i<NUM_ARRAYS_WORST_CASE; i++) {
        arrays_worst_case[i] = (long *) calloc(SIZE, sizeof(long));

        if (!arrays_worst_case[i]) {
            perror("Allocation memory error.");
            free(targets);
            targets = NULL;
            free(array);
            array = NULL;
            for (Index j=0; j<i; j++) {
                free(arrays_worst_case[j]);
                arrays_worst_case[j] = NULL;
            }
            free(arrays_worst_case);
            arrays_worst_case = NULL;
            return 1;
        }
    }

    srand(time(NULL));
    
    array[0] = MIN_VALUE;

    for (Index i=1; i<SIZE; i++) {
        array[i] = array[i-1] + (rand() % (MAX_JUMP+1));
    }
    
    clock_t start, end;

    double average_time_interpolation = 0.0f;
    double average_time_binary = 0.0f;
    double average_time_introspective = 0.0f;

    double worst_time_interpolation = 0.0f;
    double worst_time_binary = 0.0f;
    double worst_time_introspective = 0.0f;

    for (Index i=0; i<SEARCHES; i++) {
        targets[i] = (rand() % (array[SIZE-1]-array[0]+1)) + array[0];
    } 
    
    volatile Index result;

    start = clock();

    for  (Index i=0; i<SEARCHES; i++) {
        result = interpolation_search(array, SIZE, targets[i]);
    }

    end = clock();

    average_time_interpolation = (double) ((double) (end - start) / CLOCKS_PER_SEC) / SEARCHES;

    start = clock();

    for (Index i=0; i<SEARCHES; i++) {
        result = binary_search(array, SIZE, targets[i]);
    }

    end = clock();

    average_time_binary = (double) ((double) (end - start) / CLOCKS_PER_SEC) / SEARCHES;

    start = clock();
    
    for (Index i=0; i<SEARCHES; i++) {
        result = introspective_search(array, SIZE, targets[i]);   
    }

    end = clock();

    average_time_introspective = (double) ((double) (end - start) / CLOCKS_PER_SEC) / SEARCHES;

    free(targets);
    free(array);

    FILE* searching_times_in_average_case_file = fopen("searching_times_in_average_case_file.csv", "a+");

    if (!searching_times_in_average_case_file) {
        perror("File wasn't be opened.\n");
        return 2;
    }

    //fprintf(searching_times_in_average_case_file, "Nro_datos,Tiempo_interpolación(s),Tiempo_binaria(s),Tiempo_introspectiva(s)\n");
    fprintf(searching_times_in_average_case_file, "%d,%.9f,%.9f,%.9f\n", SIZE, average_time_interpolation, average_time_binary, average_time_introspective);

    fclose(searching_times_in_average_case_file);

    for (Index i=0; i<NUM_ARRAYS_WORST_CASE; i++) {
        generate_worst_case_array(arrays_worst_case[i], SIZE);
    }

    start = clock();
    
    for (Index i=0; i<SEARCHES; i++) {
        result = interpolation_search(arrays_worst_case[i % NUM_ARRAYS_WORST_CASE], 
                                      SIZE, 
                                      arrays_worst_case[i % NUM_ARRAYS_WORST_CASE][SIZE-2]);
    }
    
    end = clock();

    worst_time_interpolation = (double) ((double) (end - start) / CLOCKS_PER_SEC) / SEARCHES;

    start = clock();

    for (Index i=0; i<SEARCHES; i++) {
        result = binary_search(arrays_worst_case[i % NUM_ARRAYS_WORST_CASE], 
                                SIZE, 
                                arrays_worst_case[i % NUM_ARRAYS_WORST_CASE][(rand() % 2) * (SIZE-1)]);
    }

    end = clock();

    worst_time_binary = (double) ((double) (end - start) / CLOCKS_PER_SEC) / SEARCHES;

    start = clock();
    
    for (Index i=0; i<SEARCHES; i++) {
        result = introspective_search(arrays_worst_case[i % NUM_ARRAYS_WORST_CASE], 
                                      SIZE, 
                                      arrays_worst_case[i % NUM_ARRAYS_WORST_CASE][SIZE-2]);
    }

    end = clock();

    worst_time_introspective = (double) ((double) (end - start) / CLOCKS_PER_SEC) / SEARCHES;

    for (Index i=0; i<NUM_ARRAYS_WORST_CASE; i++) {
        free(arrays_worst_case[i]);
        arrays_worst_case[i] = NULL;
    }

    free(arrays_worst_case);
    arrays_worst_case = NULL;

    FILE* searching_times_in_worst_case_file = fopen("searching_times_in_worst_case_file.csv", "a+");

    if (!searching_times_in_worst_case_file) {
        perror("File wasn't be opened.\n");
        return 2;
    }

    //fprintf(searching_times_in_worst_case_file, "Nro_datos,Tiempo_interpolación(s),Tiempo_binaria(s),Tiempo_introspectiva(s)\n");
    fprintf(searching_times_in_worst_case_file, "%d,%.9f,%.9f,%.9f\n", SIZE, worst_time_interpolation, worst_time_binary, worst_time_introspective);

    fclose(searching_times_in_worst_case_file);

    return 0;
}
