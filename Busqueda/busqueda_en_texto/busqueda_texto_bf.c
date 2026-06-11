#include "list.h"
#include "string.h"

#define PATRON_1 "ABD"
#define PATRON_2 "AAAB"
#define PATRON_3 "XYZ"
#define PATRON_4 "AB"

#define TEXTO_1 "ABCABD"
#define TEXTO_2 "AAAAAAB"
#define TEXTO_3 "ABCDEFG"
#define TEXTO_4 "AABABC"

typedef int Index;
typedef Lista IndexList;

IndexList busqueda_secuencial_en_texto(const char* texto, const char* patron);
Index busqueda_secuencial_en_texto_primera_coincidencia(const char* texto, const char* patron);

int main() {

    Index resultado_busqueda_1_primera_coincidencia = busqueda_secuencial_en_texto_primera_coincidencia(TEXTO_1, PATRON_1);
    Index resultado_busqueda_2_primera_coincidencia = busqueda_secuencial_en_texto_primera_coincidencia(TEXTO_2, PATRON_2);
    Index resultado_busqueda_3_primera_coincidencia = busqueda_secuencial_en_texto_primera_coincidencia(TEXTO_3, PATRON_3);
    Index resultado_busqueda_4_primera_coincidencia = busqueda_secuencial_en_texto_primera_coincidencia(TEXTO_4, PATRON_4);

    printf("PRIMERA COINCIDENCIA:\n");

    if (resultado_busqueda_1_primera_coincidencia != -1) {
        printf("El patrón \"%s\" se encontró en la posición %d del texto \"%s\"\n", PATRON_1, resultado_busqueda_1_primera_coincidencia, TEXTO_1);
    }

    else
    {
        printf("El patrón \"%s\" no fue encontrado dentro de \"%s\"\n", PATRON_1, TEXTO_1);
    }

    if (resultado_busqueda_2_primera_coincidencia != -1) {
        printf("El patrón \"%s\" se encontró en la posición %d del texto \"%s\"\n", PATRON_2, resultado_busqueda_2_primera_coincidencia, TEXTO_2);
    }

    else {
        printf("El patrón \"%s\" no fue encontrado dentro de \"%s\"\n", PATRON_2, TEXTO_2);
    }

    if (resultado_busqueda_3_primera_coincidencia != -1) {
        printf("El patrón \"%s\" se encontró en la posición %d del texto \"%s\"\n", PATRON_3, resultado_busqueda_3_primera_coincidencia, TEXTO_3);
    }

    else {
        printf("El patrón \"%s\" no fue encontrado dentro de \"%s\"\n", PATRON_3, TEXTO_3);
    }

    if (resultado_busqueda_4_primera_coincidencia != -1) {
        printf("El patrón \"%s\" se encontró en la posición %d del texto \"%s\"\n", PATRON_4, resultado_busqueda_4_primera_coincidencia, TEXTO_4);
    }

    else {
        printf("El patrón \"%s\" no fue encontrado dentro de \"%s\"\n", PATRON_4, TEXTO_4);
    }

    IndexList resultado_busqueda_1 = busqueda_secuencial_en_texto(TEXTO_1, PATRON_1);
    IndexList resultado_busqueda_2 = busqueda_secuencial_en_texto(TEXTO_2, PATRON_2);
    IndexList resultado_busqueda_3 = busqueda_secuencial_en_texto(TEXTO_3, PATRON_3);
    IndexList resultado_busqueda_4 = busqueda_secuencial_en_texto(TEXTO_4, PATRON_4);

    printf("\nTODAS LAS COINCIDENCIAS:\n");

    printf("El patrón \"%s\" fue encontrado dentro del texto \"%s\" en las posiciones ", PATRON_1, TEXTO_1);
    imprimir_lista(resultado_busqueda_1);


    printf("El patrón \"%s\" fue encontrado dentro del texto \"%s\" en las posiciones ", PATRON_2, TEXTO_2);
    imprimir_lista(resultado_busqueda_2);


    printf("El patrón \"%s\" fue encontrado dentro del texto \"%s\" en las posiciones ", PATRON_3, TEXTO_3);
    imprimir_lista(resultado_busqueda_3);

    printf("El patrón \"%s\" fue encontrado dentro del texto \"%s\" en las posiciones ", PATRON_4, TEXTO_4);
    imprimir_lista(resultado_busqueda_4);

    eliminar_lista(&resultado_busqueda_1, true);
    eliminar_lista(&resultado_busqueda_2, true);
    eliminar_lista(&resultado_busqueda_3, true);
    eliminar_lista(&resultado_busqueda_4, true);

    return 0;
}

IndexList busqueda_secuencial_en_texto(const char* texto, const char* patron) {
    IndexList index_list;

    inicializar_lista(&index_list);
    crear_lista_vacia(&index_list);

    if (texto == NULL || patron == NULL) {
        return index_list;
    }

    Natural n = strlen(texto);    
    Natural m = strlen(patron);

    if (m > n) {
        return index_list;
    }

    for (Index i = 0; i <= n-m; i++) {
        bool salir = false;
        for (Index j=0; !salir && j<m; j++) {
            if (texto[i+j] != patron[j]) {
                salir = true;
            }

            if (!salir && j == m-1) {
                insertar_nodo_inicio(&index_list, i);
            }
        }
    }

    return index_list;
}

Index busqueda_secuencial_en_texto_primera_coincidencia(const char* texto, const char* patron) {
    if (texto == NULL || patron == NULL) {
        return -1;
    }

    Natural n = strlen(texto);    
    Natural m = strlen(patron);

    if (m > n) {
        return -1;
    }

    for (Index i = 0; i <= n-m; i++) {
        bool salir = false;
        for (Index j=0; !salir && j<m; j++) {
            if (texto[i+j] != patron[j]) {
                salir = true;
            }

            if (!salir && j == m-1) {
                return i;
            }
        }
    }

    return -1;
}