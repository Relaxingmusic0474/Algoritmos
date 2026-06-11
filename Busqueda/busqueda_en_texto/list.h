#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdbool.h>

#define min(x, y) ((x < y) ? x : y)
#define max(x, y) ((x > y) ? x : y)

typedef unsigned int Natural;
typedef struct nodo Nodo, NodoCircular;
typedef struct nodoDoble NodoDoble, NodoDobleCircular;
typedef struct lista Lista, ListaCircular;
typedef struct listaDoble ListaDoble;
typedef struct listaDobleCircular ListaDobleCircular;

struct nodo
{
    int dato;
    Nodo* siguiente;
};

struct lista
{
    Nodo* cabeza;
    Natural tamanho; // Número de elementos (no cuenta el centinela)
};

struct nodoDoble
{
    int dato;
    NodoDoble* siguiente;
    NodoDoble* anterior;
};

struct listaDoble
{
    NodoDoble* cabeza;
    Natural tamanho; // Número de elementos
};


struct listaDobleCircular
{
    NodoDobleCircular* cabeza;
    Natural tamanho;  // Este campo de la estructura se añadió por eficiencia
};

/* ------------ FUNCIONES PARA LISTAS ENLAZADAS SIMPLES ----------- */
void inicializar_lista(Lista* lista);
bool crear_lista_vacia(Lista* lista);
bool crear_lista(Lista* lista, Natural nro_elementos);
Nodo* nodo_k_esimo(Lista lista, int k);
bool insertar_nodo(Lista* lista, int valor, int posicion);
bool insertar_nodo_inicio(Lista* lista, int valor);
bool insertar_nodo_final(Lista* lista, int valor);
void modificar_nodo(Lista* lista, int posicion, int valor);
int buscar_valor_en_lista(Lista* lista, int valor_buscado);
void imprimir_lista(Lista lista);
Natural tamanho_lista(Lista lista);
void eliminar_nodo(Lista* lista, int posicion);
void eliminar_nodo_inicio(Lista* lista);
void eliminar_nodo_final(Lista* lista);
void eliminar_lista(Lista* lista, bool liberar);
void vaciar_lista(Lista* lista);
bool esta_vacia(Lista lista);
void intercambiar_nodos(Lista* lista, int posicion1, int posicion2);
void invertir_lista(Lista* lista);
/* --------------------------------------------------------------- */


/* ----------- FUNCIONES PARA LISTAS ENLAZADAS DOBLES ------------ */
bool crear_lista_doble(ListaDoble* lista, Natural nro_elementos);
NodoDoble* nodo_doble_k_esimo(ListaDoble lista, int k);
bool insertar_nodo_doble(ListaDoble* lista, int valor, int posicion);
bool insertar_nodo_doble_inicio(ListaDoble* lista, int valor);
bool insertar_nodo_doble_final(ListaDoble* lista, int valor);
void modificar_nodo_doble(ListaDoble* lista, int posicion, int valor);
int buscar_valor_en_lista_doble(ListaDoble* lista, int valor_buscado);
void imprimir_lista_doble(ListaDoble lista, bool invertida);
Natural tamanho_lista_doble(ListaDoble lista);
void eliminar_nodo_doble(ListaDoble* lista, int posicion);
void eliminar_nodo_doble_inicio(ListaDoble* lista);
void eliminar_nodo_doble_final(ListaDoble* lista);
void eliminar_lista_doble(ListaDoble* lista);
/* --------------------------------------------------------------- */


/* --------- FUNCIONES PARA LISTAS ENLAZADAS CIRCULARES ---------- */
void inicializar_lista_circular(ListaCircular* lista);
bool crear_lista_circular_vacia(ListaCircular* lista);
bool crear_lista_circular(ListaCircular* lista, Natural nro_elementos);
bool insertar_nodo_circular(ListaCircular* lista, int valor, int posicion);
bool insertar_nodo_circular_inicio(ListaCircular* lista, int valor);
bool insertar_nodo_circular_final(ListaCircular* lista, int valor);
void modificar_nodo_circular(ListaCircular* lista, int posicion, int valor);
int buscar_valor_en_lista_circular(ListaCircular* lista, int valor_buscado);
void imprimir_lista_circular(ListaCircular lista);
Natural tamanho_lista_circular(ListaCircular lista);
void eliminar_nodo_circular(ListaCircular* lista, int posicion);
void eliminar_nodo_circular_inicio(ListaCircular* lista);
void eliminar_nodo_circular_final(ListaCircular* lista);
void eliminar_lista_circular(ListaCircular* lista, bool liberar);
void vaciar_lista_circular(ListaCircular* lista);
bool es_circular_vacia(ListaCircular lista);
void rotacion_izquierda_lista_circular(ListaCircular* lista);
void rotacion_derecha_lista_circular(ListaCircular* lista);
/* --------------------------------------------------------------- */


/* ------ FUNCIONES PARA LISTAS ENLAZADAS CIRCULARES DOBLES ------ */
bool crear_lista_circular_doble(ListaDobleCircular* lista, Natural nro_elementos);
NodoDobleCircular* nodo_circular_doble_k_esimo(ListaDobleCircular lista, int k);
bool insertar_nodo_circular_doble(ListaDobleCircular* lista, int valor, int posicion);
bool insertar_nodo_circular_doble_inicio(ListaDobleCircular* lista, int valor);
bool insertar_nodo_circular_doble_final(ListaDobleCircular* lista, int valor);
void modificar_nodo_circular_doble(ListaDobleCircular* lista, int posicion, int valor);
int buscar_valor_en_lista_circular_doble(ListaDobleCircular* lista, int valor_buscado);
void imprimir_lista_circular_doble(ListaDobleCircular lista);
Natural tamanho_lista_circular_doble(ListaDobleCircular lista);
void eliminar_nodo_circular_doble(ListaDobleCircular* lista, int posicion);
void eliminar_nodo_circular_doble_inicio(ListaDobleCircular* lista);
void eliminar_nodo_circular_doble_final(ListaDobleCircular* lista);
void eliminar_lista_circular_doble(ListaDobleCircular* lista);
void rotacion_izquierda_lista_circular_doble(ListaDobleCircular* lista);
void rotacion_derecha_lista_circular_doble(ListaDobleCircular* lista);
/* --------------------------------------------------------------- */

#endif  // LIST_H