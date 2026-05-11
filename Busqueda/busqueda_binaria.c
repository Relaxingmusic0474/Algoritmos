/*
 * binsearch.c
 * Análisis de Algoritmos — Búsqueda Binaria
 * Se verá la versión: iterativa y recursiva.
 */

#include <stdio.h>

typedef int Index;

/* ─── Versión ITERATIVA ─────────────────────────────────────────────────── */
/*
 * Precondición: arr[] debe estar ordenado de menor a mayor.
 * Retorna el índice del elemento si lo encuentra, -1 en caso contrario.
 */
Index binsearch_iterativo(int arr[], int n, int objetivo) {
    Index izq = 0;
    Index der = n-1;

    while (izq <= der) {
        Index mid = (izq + der) >> 1;

        if (arr[mid] == objetivo) {
            return mid;
        } 
        
        else if (arr[mid] < objetivo) {
            izq = mid + 1;
        } 
        
        else {
            der = mid - 1;
        }
    }

    return -1;
}

/* ─── Versión RECURSIVA ─────────────────────────────────────────────────── */
/*
 * Precondición: arr[] debe estar ordenado de menor a mayor.
 * Llamada inicial: binsearch_recursivo(arr, 0, n-1, objetivo)
 * Retorna el índice del elemento si lo encuentra, -1 en caso contrario.
 */
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

Index binsearch(int arr[], int n, int objetivo)
{
    return binsearch_recursivo(arr, 0, n-1, objetivo);
}


/* ─── Main ──────────────────────────────────────────────────────────────── */

int main(void) {
    int arr[]  = {1, 3, 7, 9, 15, 20, 28, 36, 42, 51};
    int n      = sizeof(arr) / sizeof(arr[0]);
    int objetivo_recursivo = 28;
    int objetivo_iterativo = 4;

    /* Llamada a la versión recursiva */
    Index resultado = binsearch(arr, n, objetivo_recursivo);
    Index resultado2 = binsearch_iterativo(arr, n, objetivo_iterativo);

    /* resultado == índice encontrado  (ó -1 si no existe) */
    printf("Objetivo: arr[%d] = %d\n", resultado, objetivo_recursivo);
    printf("Objetivo: arr[%d] = %d\n", resultado2, objetivo_iterativo);

    return 0;
}
