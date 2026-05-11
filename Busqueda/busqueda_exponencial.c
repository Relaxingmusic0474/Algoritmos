#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define DATO -13

typedef int Index;

Index binsearch_recursivo(int arr[], Index izq, Index der, int objetivo) {
    if (izq > der) {
        return -1;  // Caso base: no encontrado
    }

    Index mid = (izq + der) / 2;

    if (arr[mid] == objetivo) {
        return mid;
    } 
    
    else if (arr[mid] < objetivo) {
        return binsearch_recursivo(arr, mid + 1, der, objetivo);
    } 
    
    else {
        return binsearch_recursivo(arr, izq, mid - 1, objetivo);
    }
}

/*

Index exponential_search(int arr[], size_t n, int x)
{
    Index idx = 0;

    while (idx < n && arr[idx] < x) {
        
        idx = idx << 1;
        idx++;
    }

    if (arr[idx] == x) {
        return idx;
    }

    else if (arr[idx] > x)
    {
        Index start = (idx - 1) >> 1;
        Index end = idx - 1;
        return binsearch_recursivo(arr, start, end, x);
    }

    else  // En caso que se haya agotado los indices y no llegado al numero
    {
        return -1;
    }
}

*/

Index exponential_search(int arr[], size_t n, int x)
{
    Index start_idx = 0, end_idx = 0;

    while (end_idx < n && arr[end_idx] < x) {  
        
        if (end_idx >= 1) {
            start_idx = end_idx;
        }  

        end_idx = end_idx << 1;
        end_idx++;

        printf("start_idx=%d, end_idx=%d\n", start_idx, end_idx);
    }

    if (end_idx >= n) {
        end_idx = n-1;
    }

    printf("start_idx=%d, end_idx=%d\n", start_idx, end_idx);

    if (arr[end_idx] == x) {
        return end_idx;
    }

    else if (arr[end_idx] > x)
    {
        return binsearch_recursivo(arr, start_idx+1, end_idx-1, x);
    }

    else  // En caso que se haya agotado los indices y no llegado al numero
    {
        return -1;
    }
}


int main(void) {
    int arr[] = {-10, -7, -6, -4, 0, 1, 3, 5, 8, 13, 17, 20, 22, 27, 30, 33,
                  38, 45, 52, 63, 74, 85, 100};

    size_t n = sizeof(arr) / sizeof(int);

    printf("El %d está en la posición %d del arreglo\n", DATO, exponential_search(arr, n, DATO));
    return 0;
}