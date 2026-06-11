// #include "../header/list.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------- LISTAS ENLAZADAS SIMPLES -------------------------------------------------- */
/**
 * @brief Función para inicializar una lista enlazada simple.
 * @param lista La lista que se quiere inicializar.
 */
void inicializar_lista(Lista* lista)
{
    lista->cabeza = NULL;
    lista->tamanho = 0;  // Initialize size to 0
}

/** 
 * @brief Función que crea una lista vacía (con un único nodo y que apunta a NULL).
 * @param lista La lista que se quiere crear vacía.
 * @return true si se logró crear, false en caso contrario.
 */
bool crear_lista_vacia(Lista* lista)
{
    if (!lista)
    {
        printf("Error: Puntero inválido\n");
        return false;
    }

    if (lista->cabeza)  // Si la lista ya tenía cabeza, simplemente se vacía
    {
        vaciar_lista(lista);
        return true;
    }
    
    Nodo* nodo = (Nodo *) calloc(1, sizeof(Nodo));

    if (!nodo)
    {
        printf("Error de asignación de memoria.\n");
        return false;
    }

    nodo->dato = 0;
    nodo->siguiente = NULL;
    lista->cabeza = nodo;
    return true;
}

/**
 * @brief Función que crea una lista con cierto número de elementos (e inicializa en 0 todos sus nodos).
 * @param nro_elementos Nro de elementos que tendrá la lista.
 * @return true si se creó correctamente, false en caso contrario.
 */
bool crear_lista(Lista* lista, Natural nro_elementos)
{
    Natural i;

    if (!crear_lista_vacia(lista))
    {
        printf("Error: No se pudo crear la lista.  Ni siquiera la vacía.\n");
        return false;
    }

    for (i=0; i<nro_elementos; i++)
    {
        if (!insertar_nodo_inicio(lista, 0))
        {
            eliminar_lista(lista, false);  // Se eliminan los nodos, pero se deja el centinela en caso que haya un error al crear alguno de los nodos
            printf("Error: No se pudo crear la lista completa.  Solo se pudo crear la lista vacía.\n");
            return true;  // True, ya que el nodo centinela igual ocupa memoria.
        }
    }

    lista->tamanho = nro_elementos;  // Se actualiza el campo tamanho de la lista, para que refleje el número de elementos que tiene (sin contar el nodo centinela).

    return true;
}

/**
 * @brief Función que devuelve el nodo k-ésimo de una lista enlazada.
 * @param lista La lista que se recorrerá.
 * @param k La posición del nodo de la lista, del cual se quiere obtener información.
 * @return El puntero al nodo de la posición k de la lista.
 */
Nodo* nodo_k_esimo(Lista lista, int k)
{
    if (!lista.cabeza)
    {
        return NULL;
    }

    Nodo* nodo = lista.cabeza->siguiente;
    int pos_actual = 0;

    while (nodo)
    {
        if (pos_actual == k)
        {
            return nodo;
        }

        nodo = nodo->siguiente;
        pos_actual++;
    }

    return NULL;
}

/** 
 * @brief Función que inserta un nodo en una cierta posición de la lista enlazada.
 * @param lista La lista en la cual se quiere insertar un elemento.
 * @param valor El valor del nodo que se quiere insertar.
 * @param posicion La posición deseada.
 * @return true si se pudo insertar exitosamente, false si ocurrió algún error en el proceso.
 */
bool insertar_nodo(Lista* lista, int valor, int posicion)
{
    if (!lista)
    {
        printf("Error: La lista no existe.\n");
        return false;
    }

    Nodo* nodo = calloc(1, sizeof(Nodo));

    if (!nodo)
    {
        printf("Error de asignación de memoria.\n");
        return false;
    }

    nodo->dato = valor;

    Nodo* actual = lista->cabeza->siguiente;
    Nodo* prev = lista->cabeza;

    int posicion_actual = 0;

    while (posicion_actual < posicion)
    {
        if (actual)
        {
            actual = actual->siguiente;
        }

        if (prev)
        {
            prev = prev->siguiente;
        }

        if (!actual && !prev)
        {
            printf("Error: La lista tiene menos de %hu elementos, por lo que no se puede acceder al índice %hu.\n", posicion+1, posicion);
            free(nodo);
            nodo = NULL;
            return false;
        }

        posicion_actual++;
    }

    nodo->siguiente = actual;
    prev->siguiente = nodo;
    lista->tamanho++;

    return true;
}

/**
 * @brief Función que inserta un nodo al inicio de una lista.
 * @param lista La lista a la cual se le quiere insertar un elemento al inicio.
 * @param valor Valor que tendrá el nodo que se inserte al inicio.
 * @return El valor de la función insertar_nodo con el parámetro posicion=0.
 */
bool insertar_nodo_inicio(Lista* lista, int valor)
{
    return insertar_nodo(lista, valor, 0);
}

/**
 * @brief Función que inserta un nodo al final de una lista.
 * @param lista La lista a la cual se le quiere insertar un elemento al final.
 * @param valor Valor que tendrá el nodo que se inserte al final.
 * @return El valor de la función insertar_nodo con el parámetro posicion=tamanho_lista(lista).
 */
bool insertar_nodo_final(Lista* lista, int valor)
{
    return insertar_nodo(lista, valor, tamanho_lista(*lista));
}

/**
 * @brief Función que modifica el valor de un nodo de una lista enlazada.
 * @param lista La lista enlazada que se quiere modificar.
 * @param posicion La posición secuencial del nodo que se quiere modificar (0, 1, 2, ...).
 * @param valor El valor nuevo que tendrá el nodo.
 */
void modificar_nodo(Lista* lista, int posicion, int valor)
{
    if (esta_vacia(*lista))
    {
        printf("Holi\n");
        return;
    }

    Nodo* actual = lista->cabeza->siguiente;
    Nodo* sig = actual->siguiente;

    int posicion_actual = 0;

    while (posicion_actual < posicion)
    {
        if (sig)
        {
            actual = sig;
            sig = actual->siguiente;
        }

        else
        {
            printf("Error: La lista tiene menos de %hu elementos, por lo que no se puede acceder al índice %hu.\n", posicion+1, posicion);
            return;
        }

        posicion_actual++;
    }

    actual->dato = valor;
}

/**
 * @brief Función que intenta encontrar un valor en una lista enlazada.
 * @param lista La lista en la que se buscará el valor.
 * @param valor_buscado El valor que se quiere buscar.
 * @return La posición de la lista enlazada en la cual se encontró el valor (si no se encuentra, devuelve -1).
 */
int buscar_valor_en_lista(Lista* lista, int valor_buscado)
{
    Nodo* actual;
    int pos_actual = 0;

    if (!lista || !lista->cabeza)
    {
        printf("La lista no existe o su cabeza (centinela) apunta a NULL.\n");
        return -1;
    }

    actual = lista->cabeza->siguiente;

    while (actual)
    {
        if (actual->dato == valor_buscado)
        {
            return pos_actual;
        }

        actual = actual->siguiente;
        pos_actual++;
    }

    return -1;
}

/**
 * @brief Imprime los valores almacenados en los nodos de una lista enlazada.
 * @param lista La lista que se desea imprimir.
 */
void imprimir_lista(Lista lista)
{
    if (esta_vacia(lista))
    {
        printf("NULL\n");
        return;
    }

    Nodo* actual = lista.cabeza->siguiente;

    while (actual)
    {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    }

    printf("NULL\n");
}

/** 
 * @brief Función que devuelve el tamaño (nro de nodos de una lista).
 * @param lista La lista de la cual se quiere saber su tamaño.
 * @return El número de nodos que tiene la lista.
 */
Natural tamanho_lista(Lista lista)
{
    if (!lista.cabeza)
    {
        return 0;
    }

    return lista.tamanho;
}

/**
 * @brief Función que elimina un nodo de una lista enlazada.
 * @param lista La lista enlazada de la cual se quiere eliminar un nodo.
 * @param posicion La posición del nodo que se desea eliminar.
 */
void eliminar_nodo(Lista* lista, int posicion)
{
    if (!lista)
    {
        printf("Error al eliminar: La lista simple no existe.\n");
        return;
    }
    
    if (!lista->cabeza || esta_vacia(*lista))
    {
        printf("Error al eliminar: La lista no tiene cabeza válida, o está vacía.\n");
        return;
    }

    Nodo* prev = lista->cabeza;
    Nodo* actual = lista->cabeza->siguiente;
    int posicion_actual = 0;

    while (posicion_actual < posicion)
    {
        if (actual)
        {
            prev = prev->siguiente;
            actual = actual->siguiente;
        }

        else
        {
            printf("Error: No se pudo eliminar el nodo, ya que no existe un nodo en la posición %hu.\n", posicion);
            return;
        }

        posicion_actual++;
    }
    
    prev->siguiente = actual->siguiente;
    free(actual);
    lista->tamanho--;
}

/**
 * @brief Función que elimina el primer nodo de una lista enlazada simple.
 * @param lista La lista a la cual se le quiere eliminar el primer nodo.
 */
void eliminar_nodo_inicio(Lista* lista)
{
    eliminar_nodo(lista, 0);
}

/**
 * @brief Función que elimina el último nodo de una lista enlazada simple.
 * @param lista La lista a la cual se le quiere eliminar el último nodo.
 */
void eliminar_nodo_final(Lista* lista)
{
    eliminar_nodo(lista, tamanho_lista(*lista)-1);
}

/**
 * @brief Función que elimina una lista, recorriendo nodo a nodo.
 * @param lista La lista que se quiere eliminar.
 * @param liberar Booleano que indica si se quiere eliminar completamente, liberando toda su memoria e incluso no pudiendo acceder más a ella, o si solo se quiere vaciar.
 */
void eliminar_lista(Lista* lista, bool liberar)
{
    if (!lista)
    {
        return;
    }

    if (!lista->cabeza)
    {
        return;
    }

    Nodo* actual;
    Nodo* sig;

    if (liberar)  // Cuando se quiere eliminar completamente
    {
        actual = lista->cabeza;

        while (actual)
        {
            sig = actual->siguiente;
            free(actual);
            lista->cabeza = sig;
            actual = lista->cabeza;
        }

        lista->cabeza = NULL;
    }

    else  // Cuando se quiere dejar sin nodos pero no liberar completa, sino que dejarla como lista vacía solamente
    {
        actual = lista->cabeza->siguiente;

        while (actual)
        {
            sig = actual->siguiente;
            free(actual);
            actual = sig;
        }

        lista->cabeza->dato = 0;
        lista->cabeza->siguiente = NULL;
    }

    lista->tamanho = 0;
}

/**
 * @brief Vacía una lista.
 * @param lista La lista que se vaciará.
 */
void vaciar_lista(Lista* lista)
{
    eliminar_lista(lista, false);
}

/**
 * @brief Función para saber si una lista está vacía.
 * @param lista La lista a verificar.
 * @return true si está vacía, false en caso contrario.
 */
bool esta_vacia(Lista lista)
{
    if (!lista.cabeza)
    {
        return true;
    }

    return (lista.cabeza->siguiente == NULL);
}

/**
 * @brief Función que intercambia los valores de 2 nodos en cierta posición de la lista enlazada.
 * @param lista La lista.
 * @param posicion1 La posición de uno de los nodos involucrados en el intercambio.
 * @param posicion2 La posición del otro de los nodos involucrados en el intercambio.
 */
void intercambiar_nodos(Lista* lista, int posicion1, int posicion2)
{
    Natural n = tamanho_lista(*lista);

    if (posicion1 >= n || posicion2 >= n)
    {
        printf("Error: Alguno(s) de los nodos que se quiere intercambiar, no está(n) en la lista.\n");
        return;
    }

    if (posicion1 == posicion2)
    {
        return;
    }

    Nodo* actual = lista->cabeza->siguiente;
    Nodo* nodo1, *nodo2;
    int i = 0;
    int x, y;

    while (i < min(posicion1, posicion2))
    {
        actual = actual->siguiente;
        i++;
    }

    x = actual->dato;
    nodo1 = actual;

    while (i < max(posicion1, posicion2))
    {
        actual = actual->siguiente;
        i++;
    }

    nodo2 = actual;
    y = actual->dato;

    nodo1->dato = y;
    nodo2->dato = x;

    return;
}

/**
 * @brief Función que invierte una lista.
 * @param lista Puntero a la lista que se quiere invertir.
 */
void invertir_lista(Lista* lista)
{
    Natural i;
    Natural n = tamanho_lista(*lista);

    for (i=0; i<(n+1)/2; i++)
    {
        intercambiar_nodos(lista, i, (n-1)-i);
    }

    return;
}
/* ------------------------------------------------------------------------------------------------------------------------------ */



/* -------------------------------------------------- LISTAS ENLAZADAS DOBLES -------------------------------------------------- */
/**
 * @brief Función que crea una lista doble de N elementos, e inicializa los valores de sus nodos en 0.
 * @param lista La lista doble que se creará.
 * @param nro_elementos El nro de elementos que tendrá.
 * @return true si se crea correctamente, false en caso contrario.
 */
bool crear_lista_doble(ListaDoble* lista, Natural nro_elementos)
{
    Natural i;

    for (i=0; i<nro_elementos; i++)
    {
        if (!insertar_nodo_doble_inicio(lista, 0))
        {
            eliminar_lista_doble(lista);
            printf("Error: No se pudo crear la lista doble.\n");
            return false;
        }
    }

    return true;
}

/**
 * @brief Función que devuelve el nodo en la posición k de una lista doble.
 * @param lista La lista que se recorrerá en busca del nodo.
 * @param k La posición de la lista de la cual se quiere obtener el nodo.
 * @return El puntero al nodo en la posición k de la lista doble.
 */
NodoDoble* nodo_doble_k_esimo(ListaDoble lista, int k)
{
    if (!lista.cabeza)
    {
        printf("Error: La lista no existe.\n");
        return NULL;
    }

    NodoDoble* actual = lista.cabeza;

    int pos_actual = 0;

    while (actual)
    {
        if (pos_actual < k)
        {
            actual = actual->siguiente;    
        }

        else
        {
            if (pos_actual == k)
            {
                return actual;
            }
        }

        pos_actual++;
    }

    printf("Error: Posición k fuera de índice, ya que la lista tiene solo %hu elementos.\n ", pos_actual);
    return NULL;
}

/**
 * @brief Función que inserta un nodo en una cierta posición de una lista doblemente enlazada.
 * @param lista La lista doble en la que se desea insertar un nodo (el puntero a ella).
 * @param valor El valor que contendrá el nodo que se insertará.
 * @param posicion La posición de la lista en la cual se quiere insertar el nodo.
 * @return true si el nodo se pudo insertar correctamente, false en caso contrario.
 */
bool insertar_nodo_doble(ListaDoble* lista, int valor, int posicion)
{
    if (!lista) 
    {
        printf("Error: Lista doble no existe.\n");
        return false;
    }

    NodoDoble* nodo = calloc(1, sizeof(NodoDoble));  // Se crea el nodo

    if (!nodo) 
    {
        printf("Error de asignación de memoria.\n");
        return false;
    }

    nodo->dato = valor;  // Se le asigna el valor

    // Caso lista vacía: solo aceptamos posicion == 0
    if (!lista->cabeza) 
    {
        if (posicion != 0) 
        {
            printf("Error: Índice %hu fuera de rango (lista vacía).\n", posicion);
            free(nodo);
            nodo = NULL;
            return false;
        }

        lista->cabeza = nodo;  // nodo->siguiente y nodo->anterior ya están en NULL gracias a calloc
        return true;
    }

    // Insertar al inicio
    if (posicion == 0) 
    {
        nodo->siguiente = lista->cabeza;
        nodo->anterior  = NULL;
        lista->cabeza->anterior = nodo;
        lista->cabeza = nodo;
        return true;
    }

    // Recorrer hasta la posición (o hasta el final si es append)
    NodoDoble* proximo  = lista->cabeza;
    NodoDoble* anterior = NULL;
    int pos_actual = 0;

    while (proximo && pos_actual < posicion)
    {
        anterior = proximo;
        proximo  = proximo->siguiente;
        pos_actual++;
    }

    // Si pos_actual != posicion, la posición pedida es mayor al tamaño de la lista  (ej: pediste 10 y la lista tiene 7; aquí proximo == NULL y pos_actual < posicion)
    if (pos_actual != posicion) 
    {
        printf("Error: Índice %hu fuera de rango (tamaño actual %hu).\n", posicion, pos_actual);
        free(nodo);
        nodo = NULL;
        return false;
    }

    // En este punto:
    // - si proximo != NULL, insertamos antes de 'proximo' (en medio)
    // - si proximo == NULL, insertamos al final (append)
    nodo->anterior  = anterior;
    nodo->siguiente = proximo;
    anterior->siguiente = nodo;

    if (proximo)  // Inserción en medio
    {              
        proximo->anterior = nodo;
    }                           
    
    // Si es al final, proximo == NULL y no tocamos nada más

    return true;
}

/**
 * @brief Función que inserta un nodo al inicio de una lista doble (dejándolo como 1er nodo).
 * @param lista Lista doble en la cual se quiere insertar un nodo al inicio.
 * @param valor Valor que contendrá el nodo.
 * @return true si la inserción fue exitosa, false en caso contrario.
 */
bool insertar_nodo_doble_inicio(ListaDoble* lista, int valor)
{
    return insertar_nodo_doble(lista, valor, 0);
}

/**
 * @brief Función que inserta un nodo al final de una lista doble (dejándolo como último nodo).
 * @param lista Lista doble en la cual se quiere insertar un nodo al final.
 * @param valor Valor que contendrá el nodo.
 * @return true si la inserción fue existosa, false en caso contrario.
 */
bool insertar_nodo_doble_final(ListaDoble* lista, int valor)
{
    return insertar_nodo_doble(lista, valor, tamanho_lista_doble(*lista));
}

/**
 * @brief Función que modifica el valor de un cierto nodo de una lista doble.
 * @param lista La lista doble que se quiere modificar.
 * @param posicion La posicion del nodo de la lista que se quiere modificar.
 * @param valor El nuevo valor que tendrá el nodo que se modificará.
 */
void modificar_nodo_doble(ListaDoble* lista, int posicion, int valor)
{
    if (!lista)
    {
        printf("Error: La lista no existe.\n");
        return;
    }

    NodoDoble* actual = lista->cabeza;
    int pos_actual = 0;

    while (actual)
    {
        if (pos_actual < posicion)
        {
            actual = actual->siguiente;
            pos_actual++;
        }

        else
        {
            if (pos_actual == posicion)
            {
                actual->dato = valor;
                return;
            }
        }
    }

    printf("Error: No se pudo modificar el nodo porque la posición está fuera de rango.  La lista doble tiene solo %hu elementos.\n", pos_actual);
    return;
}

/**
 * @brief Función que intenta encontrar un valor en una lista doblemente enlazada.
 * @param lista La lista doble en la que se buscará el valor.
 * @param valor_buscado El valor que se quiere buscar.
 * @return La posición de la lista enlazada doble en la cual se encontró el valor (si no se encuentra, devuelve -1).
 */
int buscar_valor_en_lista_doble(ListaDoble* lista, int valor_buscado)
{
    if (!lista)
    {
        printf("Error: La lista no existe.\n");
        return -1;
    }

    NodoDoble* actual = lista->cabeza;

    int posicion = 0;

    while (actual)
    {
        if (actual->dato == valor_buscado)
        {
            return posicion;
        }

        actual = actual->siguiente;
        posicion++;
    }

    return -1;
}

/**
 * @brief Función que imprime cada uno de los valores presentes en los nodos de una lista doble.
 * @param lista La lista a imprimir.
 * @param invertida Booleano que indica si la lista se quiere imprimir invertida, o en su sentido normal.
 */
void imprimir_lista_doble(ListaDoble lista, bool invertida)
{
    NodoDoble* actual = lista.cabeza;
    NodoDoble* anterior = NULL;

    printf("NULL ");

    if (invertida)
    {
        while (actual)
        {
            anterior = actual;
            actual = actual->siguiente;
        }

        actual = anterior;

        while (actual)
        {
            printf("<-> %d ", actual->dato);
            actual = actual->anterior;
        }

        printf("<-> NULL\n");
    }

    else
    {
        while (actual)
        {
            printf("<-> %d ", actual->dato);
            actual = actual->siguiente;
        }

        printf("<-> NULL\n");
    }
}

/**
 * @brief Función para saber el tamaño de una lista doble.
 * @param lista La lista doble de la cual se quiere saber su tamaño.
 * @return El tamaño (cantidad de nodos) de la lista doble.
 */
Natural tamanho_lista_doble(ListaDoble lista)
{
    NodoDoble* actual = lista.cabeza;
    Natural tamanho = 0;

    while (actual)
    {
        actual = actual->siguiente;
        tamanho++;
    }

    return tamanho;
}

/**
 * @brief Función que elimina un nodo de una lista doble.
 * @param lista La lista doble a la cual se le quiere eliminar el nodo.
 * @param posicion La posicion en que está el nodo que se quiere eliminar (0, 1, 2, ...).
 */
void eliminar_nodo_doble(ListaDoble* lista, int posicion)
{
    if (!lista || !lista->cabeza)
    {
        return;
    }

    NodoDoble* actual = lista->cabeza;
    NodoDoble* prev = NULL;

    int pos_actual = 0;

    while (actual)
    {
        if (pos_actual < posicion)
        {
            prev = actual;
            actual = actual->siguiente;
        }

        else
        {
            if (pos_actual == posicion)
            {
                if (prev)
                {
                    prev->siguiente = actual->siguiente;
                }

                if (actual->siguiente)
                {
                    actual->siguiente->anterior = prev;

                    if (posicion == 0)
                    {
                        lista->cabeza = actual->siguiente;
                    }
                }

                free(actual);
                return;
            }
        }    
        
        pos_actual++;
    }

    printf("Error: No se pudo eliminar el nodo doble, debido a que la posición está fuera de rango.  La lista tiene solo %hu elementos.\n", pos_actual);
    return;
}

/**
 * @brief Función que elimina el primer nodo de una lista doble.
 * @param lista La lista doble a la cual se le quiere eliminar el primer nodo.
 */
void eliminar_nodo_doble_inicio(ListaDoble* lista)
{
    eliminar_nodo_doble(lista, 0);
}

/**
 * @brief Función que elimina el último nodo de una lista doble.
 * @param lista La lista doble a la cual se le quiere eliminar el último nodo.
 */
void eliminar_nodo_doble_final(ListaDoble* lista)
{
    eliminar_nodo_doble(lista, tamanho_lista_doble(*lista)-1);
}

/**
 * @brief Función que elimina una lista doble y libera toda su memoria asignada, recorriéndola nodo a nodo.
 * @param lista La lista doble que se quiere eliminar.
 */
void eliminar_lista_doble(ListaDoble* lista)
{
    if (!lista)
    {
        printf("Error: Lista doble no existe.\n");
        return;
    }

    NodoDoble* actual = lista->cabeza;
    NodoDoble* sig;

    while (actual)
    {
        sig = actual->siguiente;
        free(actual);
        actual = sig;
    }

    lista->cabeza = NULL;
}
/* ----------------------------------------------------------------------------------------------------------------------------- */



/* ------------------------------------------------ LISTAS ENLAZADAS CIRCULARES ------------------------------------------------ */
/**
 * @brief Función para inicializar una lista enlazada circular.
 * @param lista La lista circular que se quiere inicializar.
 */
void inicializar_lista_circular(ListaCircular* lista)
{
    lista->cabeza = NULL;
    lista->tamanho = 0;  // Se inicializa el tamaño de la lista en 0.
}

/**
 * @brief Función que crea una lista circular vacía (con un solo nodo: el centinela).
 * @param lista Puntero a la lista circular que se quiere crear.
 * @return true si se crea correctamente, false si ocurre algún error.
 */
bool crear_lista_circular_vacia(ListaCircular* lista)
{
    if (!lista)
    {
        printf("Error: La lista circular no existe.\n");
        return false;
    }

    if (lista->cabeza)
    {
        vaciar_lista_circular(lista);
        return true;
    }

    NodoCircular* nodo = calloc(1, sizeof(NodoCircular));

    if (!nodo)
    {
        printf("Error de asignación de memoria.\n");
        return false;
    }

    lista->cabeza = nodo;
    lista->cabeza->siguiente = lista->cabeza;
    return true;
}

/**
 * @brief Función para crear una lista circular de N elementos.
 * @param lista Puntero a la lista circular que se quiere crear.
 * @param nro_elementos El nro de elementos (nodos) que tendrá la lista.
 * @return true si se creó la lista circular correctamente, false en caso de error.
 */
bool crear_lista_circular(ListaCircular* lista, Natural nro_elementos)
{
    Natural i;

    if (!crear_lista_circular_vacia(lista))
    {
        printf("Error: No se pudo crear la lista circular.  Ni siquiera la vacía.\n");
        return false;
    }

    for (i=0; i<nro_elementos; i++)
    {
        if (!insertar_nodo_circular_inicio(lista, 0))
        {
            eliminar_lista_circular(lista, false);  // En caso que ocurra un error en la inserción de un nodo, se elimina la lista circular, pero dejando el nodo centinela.
            printf("Error: No se pudo crear la lista circular con todos sus nodos.\n");
            return true;  // True, ya que el nodo centinela igual ocupa memoria.
        }
    }

    lista->tamanho = nro_elementos;
    return true;
}

/**
 * @brief Función para insertar un nodo en una posición específica de una lista circular.
 * @param lista La lista circular en la cual se quiere hacer la inserción.
 * @param valor El valor que contendrá el nodo que se insertará en la lista circular.
 * @param posicion La posición en la cual se insertará el nodo.
 * @return true si la inserción fue exitosa, false en caso contrario.
 */
bool insertar_nodo_circular(ListaCircular* lista, int valor, int posicion)
{
    if (!lista)
    {
        printf("Error:  Lista circular no existe.\n");
        return false;
    }

    if (!lista->cabeza)
    {
        printf("Error: La lista existe, pero aún no está creada, ya que ni siquiera tiene nodo centinela.\n");
        return false;
    }

    NodoCircular* nodo = calloc(1, sizeof(NodoCircular));

    if (!nodo)
    {
        printf("Error de asignación de memoria.\n");
        return false;
    }

    nodo->dato = valor;

    NodoCircular* prox = lista->cabeza->siguiente;
    NodoCircular* prev = lista->cabeza;

    int pos_actual = 0;

    while (pos_actual == 0 || prox != lista->cabeza->siguiente)
    {
        if (es_circular_vacia(*lista) && posicion != 0)
        {
            break;
        }

        if (pos_actual < posicion)
        {
            prev = prox;
            prox = prox->siguiente;
        }

        else
        {
            if (pos_actual == posicion)
            {
                nodo->siguiente = prox;
                prev->siguiente = nodo;
                lista->tamanho++;
                return true;
            }
        }

        pos_actual++;
    }

    printf("Error: No se pudo insertar el elemento en la lista, porque la posición estaba fuera de rango.  La lista circular tiene solo %hu elementos.\n", pos_actual);
    free(nodo);
    nodo = NULL;
    return false;
}

/**
 * @brief Función para insertar un nodo al inicio de una lista circular.
 * @param lista La lista circular en la cual se quiere insertar un nodo al inicio.
 * @param valor El valor que tendrá el nodo que se insertará al inicio en la lista circular.
 * @return true si se inserta correctamente, false en caso contrario.
 */
bool insertar_nodo_circular_inicio(ListaCircular* lista, int valor)
{
    return insertar_nodo_circular(lista, valor, 0);
}

/**
 * @brief Función para insertar un nodo al final de una lista circular, dejándolo como último nodo.
 * @param lista La lista circular en la cual se quiere insertar un nodo al final.
 * @param valor El valor que tendrá el nodo que se insertará al final en la lista circular.
 * @return true si se inserta correctamente, false en caso contrario.
 */
bool insertar_nodo_circular_final(ListaCircular* lista, int valor)
{
    return insertar_nodo_circular(lista, valor, tamanho_lista_circular(*lista));
}

/**
 * @brief Función para modificar el valor de un cierto nodo de una lista circular.
 * @param lista La lista circular a modificar.
 * @param posicion La posición en la que está el nodo que se quiere modificar (0, 1, 2, ...).
 * @param valor El nuevo valor que tendrá el nodo.
 */
void modificar_nodo_circular(ListaCircular* lista, int posicion, int valor)
{
    if (!lista || !lista->cabeza || es_circular_vacia(*lista))
    {
        printf("Error al modificar: La lista circular no existe, o bien, está vacía.\n");
        return;
    }

    NodoCircular* actual = lista->cabeza->siguiente;
    int posicion_actual = 0;

    while (actual != lista->cabeza || posicion_actual == 0)
    {
        if (posicion_actual < posicion)
        {
            actual = actual->siguiente;
        }

        else
        {
            if (posicion_actual == posicion)
            {
                actual->dato = valor;
                return;
            }
        }

        posicion_actual++;
    }

    printf("Error al modificar: Índice fuera de rango.  La lista circular tiene solo %hu elementos.\n", posicion_actual);
    return;
}

/**
 * @brief Función que intenta encontrar un valor en una lista enlazada circular.
 * @param lista La lista circular en la que se buscará el valor.
 * @param valor_buscado El valor que se quiere buscar.
 * @return La posición de la lista enlazada circular en la cual se encontró el valor (si no se encuentra, devuelve -1).
 */
int buscar_valor_en_lista_circular(ListaCircular* lista, int valor_buscado)
{
    if (!lista || !lista->cabeza)
    {
        printf("La lista circular no existe o su cabeza es NULL.\n");
        return -1;
    }

    if (es_circular_vacia(*lista))
    {
        printf("La lista circular está vacía.\n");
        return -1;
    }

    NodoCircular* actual = lista->cabeza->siguiente;
    int pos_actual = 0;

    while (actual != lista->cabeza)
    {
        if (actual->dato == valor_buscado)
        {
            return pos_actual;
        }

        actual = actual->siguiente;
        pos_actual++;
    }

    return -1;
}

/**
 * @brief Función para imprimir una lista circular.
 * @param lista La lista circular que se quiere imprimir.
 */
void imprimir_lista_circular(ListaCircular lista)
{
    if (!(lista.cabeza))
    {
        printf("Error: La lista circular existe pero no tiene centinela.\n");
        return;
    }

    if (es_circular_vacia(lista))
    {
        printf("Ciclo()\n");
        return;
    }
    
    NodoCircular* actual = lista.cabeza->siguiente;

    printf("Ciclo(");

    while (1)
    {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;

        if (actual == lista.cabeza)
        {
            printf(")\n");
            return;
        }
    }
}

/**
 * @brief Función para saber el tamaño de una lista circular (cantidad de nodos).
 * @param lista La lista circular de la cual se quiere obtener su tamaño.
 * @return El tamaño (nro de nodos) de la lista circular.
 */
Natural tamanho_lista_circular(ListaCircular lista)
{
    if (!(lista.cabeza))
    {
        printf("Error: La lista existe pero no tiene cabeza.\n");
        return 0;
    }

    if (es_circular_vacia(lista))
    {
        return 0;
    }

    return lista.tamanho;
}

/**
 * @brief Función para eliminar un nodo de una lista circular de una determinada posición.
 * @param lista La lista circular de la cual se quiere eliminar el nodo.
 * @param posicion La posición en la que está el nodo que se desea eliminar (0, 1, 2, ...)
 */
void eliminar_nodo_circular(ListaCircular* lista, int posicion)
{
    if (!lista)
    {
        printf("Error: La lista circular no existe.\n");
        return;
    }

    if (!lista->cabeza)
    {
        printf("Error: La lista circular existe, pero no hay centinela.\n");
        return;
    }

    if (es_circular_vacia(*lista))
    {
        printf("Error: La lista circular está vacía.  No se pueden eliminar nodos.\n");
        return;
    }

    NodoCircular* prev = lista->cabeza;
    NodoCircular* actual = lista->cabeza->siguiente;
    int pos_actual = 0;

    while (actual != lista->cabeza)
    {
        if (pos_actual < posicion)
        {
            prev = actual;
            actual = actual->siguiente;
        }

        else
        {
            if (pos_actual == posicion)
            {
                prev->siguiente = actual->siguiente;
                free(actual);
                lista->tamanho--;
                return;
            }
        }

        pos_actual++;   
    }

    printf("Error: No se pudo eliminar el nodo, porque la posición estaba fuera de rango.\n");
    return;
}

/**
 * @brief Función que elimina el nodo inicial de una lista circular.
 * @param lista La lista circular de la cual se quiere eliminar el nodo inicial.
 */
void eliminar_nodo_circular_inicio(ListaCircular* lista)
{
    eliminar_nodo_circular(lista, 0);
}

/**
 * @brief Función que elimina el último nodo de una lista circular.
 * @param lista La lista circular de la cual se quiere eliminar el último nodo.
 */
void eliminar_nodo_circular_final(ListaCircular* lista)
{
    eliminar_nodo_circular(lista, tamanho_lista_circular(*lista)-1);
}

/**
 * @brief Función para eliminar una lista circular, liberando toda su memoria.
 * @param lista La lista circular que se quiere eliminar.
 * @param liberar Booleano que indica si se quiere eliminar completamente, liberando toda su memoria e incluso no pudiendo acceder más a ella, o si solo se quiere vaciar.
 */
void eliminar_lista_circular(ListaCircular* lista, bool liberar)
{
    if (!lista)
    {
        printf("Error: La lista circular no existe.\n");
        return;
    }

    NodoCircular* actual = lista->cabeza->siguiente;
    NodoCircular* temp;

    while (actual != lista->cabeza)
    {
        temp = actual->siguiente;
        free(actual);
        actual = temp;
    }

    if (liberar)
    {
        free(lista->cabeza);
        lista->cabeza = NULL;
    }

    else
    {
        lista->cabeza->siguiente = lista->cabeza;
    }

    lista->tamanho = 0;
}

/**
 * @brief Función que vacía una lista circular, eliminándola casi completa pero dejando el nodo centinela.
 * @param lista La lista circular que se quiere vaciar.
 */
void vaciar_lista_circular(ListaCircular* lista)
{
    if (es_circular_vacia(*lista))
    {
        return;
    }

    eliminar_lista_circular(lista, false);
    lista->cabeza->dato = 0;
}

/**
 * @brief Función para saber si una lista circular está vacía o no.
 * @param lista La lista circular de la cual se quiere saber si está vacía o no.
 * @return true si está vacía, false en caso contrario.
 */
bool es_circular_vacia(ListaCircular lista)
{
    if (!(lista.cabeza))
    {
        return false;
    }

    return (lista.cabeza->siguiente == lista.cabeza);
}

/**
 * @brief Función que implementa la rotación a la izquierda de una lista circular.
 * @param lista La lista circular a la cual se le implementará una rotación a la izquierda.
 */
void rotacion_izquierda_lista_circular(ListaCircular* lista)
{
    if (!lista || !lista->cabeza)
    {
        printf("Error: La lista circular no existe, o bien su nodo centinela no está implementado.\n");
        return;
    }

    if (es_circular_vacia(*lista))  // Si está vacía no hace nada.
    {
        return;
    }

    if (lista->cabeza->siguiente->siguiente == lista->cabeza)  // Si tiene un solo elemento no hace nada.
    {
        return;
    }

    NodoCircular* primero = lista->cabeza->siguiente;

    lista->cabeza->siguiente = lista->cabeza->siguiente->siguiente;
    primero->siguiente = lista->cabeza;

    NodoCircular* actual = lista->cabeza->siguiente;

    while (actual->siguiente != lista->cabeza)
    {
        actual = actual->siguiente;
    }

    actual->siguiente = primero;
}

/**
 * @brief Función que implementa la rotación a la derecha de una lista circular.
 * @param lista La lista circular a la cual se le implementará una rotación a la derecha.
 */
void rotacion_derecha_lista_circular(ListaCircular* lista)
{
    if (!lista || !lista->cabeza)
    {
        printf("Error: La lista circular no existe, o bien su nodo centinela no está implementado.\n");
        return;
    }

    if (es_circular_vacia(*lista))  // Si está vacía no hace nada.
    {
        return;
    }

    if (lista->cabeza->siguiente->siguiente == lista->cabeza)  // Si tiene un solo elemento no hace nada.
    {
        return;
    }

    NodoCircular* penultimo = lista->cabeza;
    NodoCircular* ultimo = lista->cabeza->siguiente;  // Se tratará de buscar el último elemento de la lista circular con este puntero

    while (ultimo->siguiente != lista->cabeza)
    {
        penultimo = ultimo;
        ultimo = ultimo->siguiente;
    }

    ultimo->siguiente = lista->cabeza->siguiente;
    penultimo->siguiente = lista->cabeza;
    lista->cabeza->siguiente = ultimo;
}
/* ----------------------------------------------------------------------------------------------------------------------------- */


/* -------------------------------------------- LISTAS ENLAZADAS CIRCULARES DOBLES --------------------------------------------- */
/**
 * @brief Función que crea e inicializa una lista circular doble con un cierto número de elementos.
 * @param lista La lista circular doble a crear.
 * @param nro_elementos El número de elementos que tendrá la lista circular.
 * @return true si la creación fue exitosa, false en caso contrario.
 */
bool crear_lista_circular_doble(ListaDobleCircular* lista, Natural nro_elementos)
{
    Natural i;

    for (i=0; i<nro_elementos; i++)
    {
        if (!insertar_nodo_circular_doble(lista, 0, 0))
        {
            eliminar_lista_circular_doble(lista);
            printf("Error: No se pudo crear la lista correctamente.\n");
            return false;
        }
    }

    return true;
}

/**
 * @brief Función que devuelve el nodo k-ésimo de una lista circular doblemente enlazada (partiendo de 0).
 * @param lista La lista circular doble que se recorrerá.
 * @param k La posición del nodo que nos interesa (0, 1, 2, ...).
 * @return El puntero al nodo deseado de la lista circular doble.
 */
NodoDobleCircular* nodo_circular_doble_k_esimo(ListaDobleCircular lista, int k)
{
    if (!(lista.cabeza))
    {
        printf("Error: La lista doble está vacía.\n");
        return NULL;
    }

    NodoDobleCircular* actual = lista.cabeza;
    int posicion_actual = 0;

    while (actual != lista.cabeza || posicion_actual == 0)
    {
        if (posicion_actual < k)
        {
            actual = actual->siguiente;
        }

        else
        {
            if (posicion_actual == k)
            {
                return actual;
            }
        }

        posicion_actual++;
    }

    printf("Error: Índice fuera de rango.  La lista circular doble tiene solo %hu elementos.\n", lista.tamanho);
    return NULL;
}

/**
 * @brief Función que inserta un nodo con cierto valor en una posición específica de una lista circular doble.
 * @param lista La lista doble en la cual se insertará el nodo.
 * @param valor El valor que contendrá el nodo que se insertará en la lista circular doble.
 * @param posicion La posición relativa a la lista en la cual se insertará el nodo (0, 1, 2, ...).
 * @return true si el nodo se insertó correctamente, false en caso de error en la inserción.
 */
bool insertar_nodo_circular_doble(ListaDobleCircular* lista, int valor, int posicion)
{
    if (!lista)
    {
        printf("Error: La lista no existe.\n");
        return false;
    }

    NodoDobleCircular* nodo = calloc(1, sizeof(NodoDobleCircular));

    if (!nodo)
    {
        printf("Error de asignación de memoria.\n");
        return false;
    }

    nodo->dato = valor;
    
    // Caso de insertar en lista doble vacía
    if (!lista->cabeza)  
    {
        lista->cabeza = nodo;
        nodo->siguiente = lista->cabeza;
        nodo->anterior = lista->cabeza;
        lista->tamanho = 1;
        return true;
    }

    NodoDobleCircular* siguiente = lista->cabeza;  // Inicializamos el nodo siguiente en el primer nodo de la lista
    NodoDobleCircular* anterior = lista->cabeza->anterior;  // El anterior lo inicializamos en el último
    int posicion_actual;

    // Caso de inserción al inicio o al final
    if (posicion == 0 || posicion == lista->tamanho)
    {
        nodo->siguiente = siguiente;
        nodo->anterior = anterior;
        siguiente->anterior = nodo;
        anterior->siguiente = nodo;
    
        if (posicion == 0)
        {
            lista->cabeza = nodo;  // Si es el caso de inserción al inicio, se cambia la cabeza
        }
    }

    else
    {
        if (posicion > lista->tamanho)
        {
            printf("Error: Índice fuera de rango.  La lista circular doble tiene solo %hu elementos.\n", lista->tamanho);
            free(nodo);
            nodo = NULL;
            return false;
        }

        if (posicion > (lista->tamanho)/2)
        {
            posicion_actual = lista->tamanho;

            while (posicion_actual > posicion)
            {
                siguiente = siguiente->anterior;  // Primero se refiere al actual.  Se utilizó la misma variable para ahorrar memoria RAM.
                anterior = anterior->anterior;
                posicion_actual--;
            }
        }

        else
        {
            posicion_actual = 0;

            while (posicion_actual < posicion)
            {
                siguiente = siguiente->siguiente;
                anterior = anterior->siguiente;
                posicion_actual++;
            }
        }
        
        nodo->siguiente = siguiente;
        nodo->anterior = anterior;
        siguiente->anterior = nodo;
        anterior->siguiente = nodo;
    }

    (lista->tamanho)++;
    return true;
}

/**
 * @brief Función que inserta un nodo al inicio de una lista circular doble.
 * @param lista La lista circular doble a la cual se le quiere insertar un nodo al inicio.
 * @param valor El valor que tendrá el nodo que se insertará al inicio.
 * @return El resultado de la función insertar_nodo_circular_doble, con el parámetro posición igual a 0.
 */
bool insertar_nodo_circular_doble_inicio(ListaDobleCircular* lista, int valor)
{
    return insertar_nodo_circular_doble(lista, valor, 0);
}

/**
 * @brief Función que inserta un nodo al final de una lista circular doble.
 * @param lista La lista circular doble a la cual se le quiere insertar un nodo al final.
 * @param valor El valor que tendrá el nodo que se insertará al final.
 * @return El resultado de la función insertar_nodo_circular_doble, con el parámetro posición igual al tamaño de la lista.
 */
bool insertar_nodo_circular_doble_final(ListaDobleCircular* lista, int valor)
{
    return insertar_nodo_circular_doble(lista, valor, tamanho_lista_circular_doble(*lista));
}

/**
 * @brief Función para modificar un cierto nodo de una lista circular doble.
 * @param lista La lista que se quiere modificar.
 * @param posicion La posición en la que se encuentra el nodo a modificar.
 * @param valor El nuevo valor que tendrá el nodo.
 */
void modificar_nodo_circular_doble(ListaDobleCircular* lista, int posicion, int valor)
{
    if (!lista)
    {
        printf("Error: La lista circular doble no existe.\n");
        return;
    }

    NodoDobleCircular* objetivo = nodo_circular_doble_k_esimo(*lista, posicion);

    if (!objetivo)
    {
        return;
    }

    objetivo->dato = valor;
}

/**
 * @brief Función que intenta encontrar un valor en una lista enlazada circular doble.
 * @param lista La lista circular doble en la que se buscará el valor.
 * @param valor_buscado El valor que se quiere buscar.
 * @return La posición de la lista enlazada circular doble en la cual se encontró el valor (si no se encuentra, devuelve -1).
 */
int buscar_valor_en_lista_circular_doble(ListaDobleCircular* lista, int valor_buscado)
{
    if (!lista)
    {
        printf("Error al buscar: La lista circular doble no existe.\n");
        return -1;
    }

    if (!lista->cabeza)
    {
        printf("Error al buscar: La lista circular doble está vacía.\n");
        return -1;
    }

    NodoDobleCircular* actual = lista->cabeza;

    int posicion_actual = 0;

    while (actual != lista->cabeza || posicion_actual == 0)
    {
        if (actual->dato == valor_buscado)
        {
            return posicion_actual;
        }

        actual = actual->siguiente;
        posicion_actual++;
    }

    return -1;
}

/**
 * @brief Función que imprime los elementos de una lista circular de forma secuencial.
 * @param lista La lista circular que se quiere imprimir.
 */
void imprimir_lista_circular_doble(ListaDobleCircular lista)
{
    if (!(lista.cabeza))
    {
        printf("Ciclo()\n");
        return;
    }

    NodoDobleCircular* actual = lista.cabeza;
    Natural datos_mostrados = 0;

    printf("Ciclo(");

    while (datos_mostrados < lista.tamanho)
    {
        if (datos_mostrados == 0)
        {
            printf(" <-> ");
        }

        printf("%d <-> ", actual->dato);
        datos_mostrados++;
        actual = actual->siguiente;
    }

    printf(")\n");
}

/**
 * @brief Función para saber el tamaño de una lista circular doble.
 * @param lista Lista a la cual se le quiere determinar el tamaño.
 * @return El número de elementos (nodos) de la lista circular doble.
 */
Natural tamanho_lista_circular_doble(ListaDobleCircular lista)
{
    return lista.tamanho;
}

/**
 * @brief Función para eliminar un nodo de una posición específica de una lista circular doble.
 * @param lista La lista de la cual se quiere eliminar un nodo.
 * @param posicion La posición en la cual se encuentra el nodo que se quiere eliminar.
 */
void eliminar_nodo_circular_doble(ListaDobleCircular* lista, int posicion)
{
    if (!lista)
    {
        printf("Error al eliminar: La lista circular doble no existe.\n");
        return;
    }

    if (!lista->cabeza)
    {
        printf("Error al eliminar: La lista circular doble está vacía, porque la cabeza apunta a NULL.\n");
        return;
    }

    if (posicion >= lista->tamanho)
    {
        printf("Error al eliminar: Índice fuera de rango.  La lista circular tiene solo %hu elementos.\n", lista->tamanho);
        return;
    }

    if (lista->tamanho == 1)  // Por seguridad, si hay un solo elemento, se toma como caso especial, y se elimina la lista (para asegurarse que la cabeza quede en NULL)
    {
        eliminar_lista_circular_doble(lista);
        return;
    }

    NodoDobleCircular* actual = lista->cabeza;
    int posicion_actual;

    if (posicion > lista->tamanho / 2)
    {
        actual = actual->anterior;
        posicion_actual = lista->tamanho - 1;

        while (posicion_actual > posicion)
        {
            actual = actual->anterior;
            posicion_actual--;
        }
    }

    else
    {
        posicion_actual = 0;

        while (posicion_actual < posicion)
        {
            actual = actual->siguiente;
            posicion_actual++;
        }
    }

    if (posicion == 0)
    {
        lista->cabeza = lista->cabeza->siguiente;
    }

    actual->anterior->siguiente = actual->siguiente;
    actual->siguiente->anterior = actual->anterior;
    free(actual);
    actual = NULL;
    (lista->tamanho)--;
}

/**
 * @brief Función para eliminar el primer nodo de una lista circular doble.
 * @param lista La lista circular doble a la cual se le quiere eliminar su primer nodo.
 */
void eliminar_nodo_circular_doble_inicio(ListaDobleCircular* lista)
{
    eliminar_nodo_circular_doble(lista, 0);
}

/**
 * @brief Función para eliminar el último nodo de una lista circular doble.
 * @param lista La lista circular doble a la cual se le quiere eliminar su último nodo.
 */
void eliminar_nodo_circular_doble_final(ListaDobleCircular* lista)
{
    eliminar_nodo_circular_doble(lista, lista->tamanho-1);
}

/**
 * @brief Función que elimina una lista circular doble, liberando la memoria de todos sus nodos y dejándola vacía.
 * @param lista La lista circular doble que se quiere eliminar.
 */
void eliminar_lista_circular_doble(ListaDobleCircular* lista)
{
    if (!lista)
    {
        printf("Error: La lista no existe.\n");
        return;
    }

    if (!lista->cabeza)  
    {
        return;  // Si está vacía no hace nada
    }

    NodoDobleCircular* nodo = lista->cabeza->siguiente;
    NodoDobleCircular* temp;

    while (nodo != lista->cabeza)
    {
        temp = nodo->siguiente;
        free(nodo);
        nodo = temp;
    }

    free(lista->cabeza);
    lista->cabeza = NULL;
    lista->tamanho = 0;
}

/**
 * @brief Función que rota los elementos de una lista circular doble hacia la izquierda.
 * @param lista La lista circular doble a rotar.
 */
void rotacion_izquierda_lista_circular_doble(ListaDobleCircular* lista)
{
    if (!lista)
    {
        printf("Error al rotar: La lista circular doble no existe.\n");
        return;
    }

    if (!lista->cabeza)
    {
        printf("Error al rotar: La lista circular doble está vacía.\n");
        return;
    }

    if (lista->tamanho == 1)
    {
        return;
    }

    lista->cabeza = lista->cabeza->siguiente;  // La cabeza se corre a la derecha para que rote a la izquierda.
}

/**
 * @brief Función que rota los elementos de una lista circular doble hacia la derecha.
 * @param lista La lista circular doble a rotar.
 */
void rotacion_derecha_lista_circular_doble(ListaDobleCircular* lista)
{
    if (!lista)
    {
        printf("Error al rotar: La lista circular doble no existe.\n");
        return;
    }

    if (!lista->cabeza)
    {
        printf("Error al rotar: La lista circular doble está vacía.\n");
        return;
    }

    if (lista->tamanho == 1)
    {
        return;
    }

    lista->cabeza = lista->cabeza->anterior;  // La cabeza se corre a la izquierda para que rote a la derecha.
}
/* ----------------------------------------------------------------------------------------------------------------------------- */
