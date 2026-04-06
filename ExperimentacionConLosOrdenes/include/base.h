#ifndef BASE_H  
#define BASE_H  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
  
/* ── Configuración ──────────────────────────────── */  
  
#define NUM_VALUES 10001    // [0, N - 1]  
#define DATA_DIR "db/"  

typedef unsigned int Index;
typedef float Real;

/* ── Struct de resultado ────────────────────────── */  
  
typedef struct {  
    int n;  
    double time_f1;  
    double time_f2;  
    double time_f3;  
} ExecResults;  
  
/* ── Declaraciones ──────────────────────────────── */  

void f1(Real n);  
void f2(Real n);  
void f3(Real n);  
void run_experiment(void);

#endif