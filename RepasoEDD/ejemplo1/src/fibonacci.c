#include "fibonacci.h"
#include "limits.h"

#define ERROR UINT_MAX

NaturalGrande fibonacci_iter(Natural n)
{
    if (n == 0)
    {
        return ERROR;
    }

    Natural i;
    NaturalGrande S1=0, S2=1;

    if (n == 1)
    {
        return S1;
    }

    if (n == 2)
    {
        return S2;
    }

    NaturalGrande S; 

    for (i=3; i<=n; i++)
    {
        S = S1 + S2;
        S1 = S2;
        S2 = S;
    }

    return S;
}

NaturalGrande fibonacci_rec(Natural n)
{
    if (n == 0)
    {
        return ERROR;
    }

    if (n == 1)
    {
        return 0;
    }

    if (n == 2)
    {
        return 1;
    }

    return fibonacci_rec(n-1) + fibonacci_rec(n-2);
}
