#ifndef BASE_H  
#define BASE_H  
  
#include <stdio.h>  
#include <stdlib.h>
#include <stdbool.h>  
#include <time.h>  
  
/* ── Configuración ──────────────────────────────── */  
  
#define NUM_VALUES 10001    // [0, N - 1]  
#define DATA_DIR "db/"  

typedef int ElemType;
typedef unsigned int Index;
typedef unsigned int Natural;
typedef float Real;

/* ── Struct de resultado ────────────────────────── */  
  
typedef struct {  
    int n;  
    double time_f1;  
    double time_f2;  
    double time_f3;  
    double time_f4;
    double time_msort;
} ExecResults;  
  
/* ── Declaraciones ──────────────────────────────── */  

void f1(Real n);  
void f2(Real n);  
void f3(Real n);  
void f4(Real n);  
void mergesort(ElemType data[], size_t n, bool ascending);
void run_experiment(void);

#endif