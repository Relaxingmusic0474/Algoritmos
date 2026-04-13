#include "base.h"

// T(n) = n
void f1(Real n)
{
    volatile Real x = 0;

    for (Index i=0; i<n; i++)
    {
        x += i;
    }
}

// T(n) = 3n
void f2(Real n)
{
    volatile Real x = 0;

    while (n >= 0)
    {
        x += n;
        n -= 1./3;
    }
}

// T(n) = 10n
void f3(Real n)
{
    volatile Real x = 0;

    while (n >= 0)
    {
        x += n;
        n -= 0.1;
    }
}

// T(n) = n² ->  (O(n²))
void f4(Real n)
{
    Real x = 0;

    for (Real i = 0; i < n; i++)
    {
        for (Real j = 0; j < n; j++)
        {
            x += i*j;
        }
    }
}

/**
 * @brief Función que combina dos subarreglos ordenados en un solo arreglo ordenado.
 * @param data Arreglo donde se almacenarán los datos ordenados.
 * @param group_1 Primer subarreglo a combinar.
 * @param n1 Tamaño del primer subarreglo.
 * @param group_2 Segundo subarreglo a combinar.
 * @param n2 Tamaño del segundo subarreglo.
 * @param ascending Booleano que indica si el orden es ascendente o descendente.
 */
void merge(ElemType data[], ElemType group_1[], size_t n1, ElemType group_2[], size_t n2, bool ascending)
{
    Index i=0, j=0, k=0;

    while (i<n1 && j<n2)
    {
        if (group_1[i] > group_2[j])
        {
            if (ascending)
            {
                data[k] = group_2[j];
                j++;
            }

            else
            {
                data[k] = group_1[i];
                i++;
            }
        }

        else  // data1->arreglo[i].elemento.valor_double <= data2->arreglo[j].elemento.valor_double
        {
            if (ascending)
            {
                data[k] = group_1[i];
                i++;
            }

            else
            {
                data[k] = group_2[j];
                j++;
            }
        }

        k++;
    }

    while (i<n1)
    {
        data[k] = group_1[i];
        i++, k++;
    }

    while (j<n2)
	{
        data[k] = group_2[j];
        j++, k++;
    }
}

/**
 * @brief Función que divide un arreglo hasta que queden puros subarreglos de un solo elemento.
 * @param data Arreglo con los datos a ordenar.
 * @param n Tamaño del arreglo.
 * @param ascending Booleano que le da la libertad al programador (o en algunos casos al usuario) de si quiere que el arreglo se ordene de forma ascendente o descendente.
 */
void mergesort(ElemType data[], size_t n, bool ascending)
{
    Index i, j;
    size_t n1, n2;

    if (n <= 1)
    {
        return;
    }

    n1 = n / 2;
    n2 = n - n1;
    
    ElemType group_1[n1], group_2[n2];

    for (i=0; i<n1; i++)
    {
        group_1[i] = data[i];
    }

    for (j=0; j<n2; i++, j++)
    {
        group_2[j] = data[i];
    }

    mergesort(group_1, n1, ascending);
    mergesort(group_2, n2, ascending);
    merge(data, group_1, n1, group_2, n2, ascending);
}