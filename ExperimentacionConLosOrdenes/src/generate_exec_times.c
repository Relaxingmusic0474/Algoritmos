#include "base.h"

void run_experiment(void)
{
    /* El array debe tener espacio para cada valor de n con paso 10: (NUM_VALUES/10)+1 */
    ExecResults resultados[(NUM_VALUES / 10) + 1];
    int struct_idx = 0;

    FILE *file = fopen(DATA_DIR "comparar_Ns.csv", "w");
    if (file == NULL) {
        printf("Error al crear archivo CSV\n");
        return;
    }

    /* Encabezado CSV */
    fprintf(file, "n,time_f1,time_f2,time_f3,time_f4\n");

    /* Encabezado Terminal */
    printf("n, f1 (s), f2 (s), f3 (s), f4 (s)\n");
    printf("--------------------------------------\n");

    for (Natural n = 0; n <= NUM_VALUES; n += 10) {

        ElemType* data = NULL; 
        clock_t start, end;

        if (n == 0)
        {
            data = (ElemType*) calloc(1, sizeof(ElemType)); // Reservar espacio para un solo elemento
        }

        else
        {
            data = (ElemType*) calloc(n, sizeof(ElemType)); // Reservar espacio para n elementos
        }

        if (data == NULL) 
        {
            printf("Experimento fallido: Error al reservar memoria\n");
            return;
        }

        for (Index i=0; i<n; i++)
        {
            data[i] = (rand() % 1001) - 500;  // Datos aleatorios entre -500 y 500
        }

        /* Tiempos f1 */
        start = clock();
        f1(n);
        end = clock();
        double time_f1 = (double)(end - start) / CLOCKS_PER_SEC;

        /* Tiempos f2 */
        start = clock();
        f2(n);
        end = clock();
        double time_f2 = (double)(end - start) / CLOCKS_PER_SEC;

        /* Tiempos f3 */
        start = clock();
        f3(n);
        end = clock();
        double time_f3 = (double)(end - start) / CLOCKS_PER_SEC;

        /* Tiempos f4 */
        start = clock();
        f4(n);
        end = clock();
        double time_f4 = (double)(end - start) / CLOCKS_PER_SEC;

        /* Tiempos mergesort */
        start = clock();
        mergesort(data, n, true);
        end = clock();
        double time_mergesort = (double)(end - start) / CLOCKS_PER_SEC;

        free(data);  // Liberar memoria del array

        /* Guardar resultados (una sola vez por valor de n) */
        resultados[struct_idx].n = n;
        resultados[struct_idx].time_f1 = time_f1;
        resultados[struct_idx].time_f2 = time_f2;
        resultados[struct_idx].time_f3 = time_f3;
        resultados[struct_idx].time_f4 = time_f4;
        resultados[struct_idx].time_msort = time_mergesort;

        /* Guardar en CSV */
        fprintf(file,
                "%d,%f,%f,%f,%f,%f\n",
                resultados[struct_idx].n,
                resultados[struct_idx].time_f1,
                resultados[struct_idx].time_f2,
                resultados[struct_idx].time_f3,
                resultados[struct_idx].time_f4,
                resultados[struct_idx].time_msort);

        /* Mostrar en terminal */
        printf("%d %f %f %f %f %f\n",
               resultados[struct_idx].n,
               resultados[struct_idx].time_f1,
               resultados[struct_idx].time_f2,
               resultados[struct_idx].time_f3,
               resultados[struct_idx].time_f4,
               resultados[struct_idx].time_msort
            );

        struct_idx++;

        /* seguridad: evitar overflow accidental */
        if (struct_idx >= (int)(sizeof(resultados) / sizeof(resultados[0]))) {
            break;
        }
        
        // Dentro del ciclo hay más código que incorporaremos.
    }

    fclose(file);
    printf("\nDatos guardados en comparar_Ns.csv\n");
    // A PARTIR DE ACÁ SIGUEN LOS DEMÁS BLOQUES DE CÓDIGO, NO OLVIDES!
}