#include <stdio.h>

#define ELEMENTS 50000

void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) 
{
    int pivot = arr[high];   // pivote = último elemento
    int i = low - 1;         // índice del menor elemento

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);  // pivote a su posición
    return i + 1;
}

void quicksort(int arr[], int low, int high) 
{
    if (low < high) {
        int p = partition(arr, low, high);
        quicksort(arr, low, p - 1);
        quicksort(arr, p + 1, high);
    }
}

int main() 
{
    int arr[ELEMENTS] = {0};
    for (int i=0; i<ELEMENTS; i++) arr[i] = i;
    quicksort(arr, 0, ELEMENTS - 1);
    for (int i = 0; i < ELEMENTS; i++) printf("%d ", arr[i]);
    return 0;
}