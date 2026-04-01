#include "stdio.h"
#include "fibonacci.h"

int main()
{
    Natural n = 45;
    printf("El número %hu de la secuencia de Fibonacci es: %u\n", n, fibonacci_rec(n));
    return 0;
}
