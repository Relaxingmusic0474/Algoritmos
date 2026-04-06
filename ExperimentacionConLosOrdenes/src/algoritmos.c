#include "base.h"

// T(n) = n
void f1(Real n)
{
    while (n >= 0)
    {
        n--;
    }
}

// T(n) = 3n
void f2(Real n)
{
    while (n >= 0)
    {
        n -= 1./3;
    }
}

// T(n) = 10n
void f3(Real n)
{
    while (n >= 0)
    {
        n -= 0.1;
    }
}