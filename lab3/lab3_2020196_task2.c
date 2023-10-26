// Khizar Ali Shah - 2020196 Lab 3 Fibonacci
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        int x, y;

#pragma omp task shared(x)
        x = fibonacci(n - 1);
#pragma omp task shared(y)
        y = fibonacci(n - 2);
#pragma omp taskwait
        return x + y;
    }
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Enter the number of sequence!\n");
        exit(1);
    }
    int n = atoi(argv[1]);
    int sum = 0;

#pragma omp parallel
    {
#pragma omp single
        sum = fibonacci(n);
    }

    printf("Sum of Fib numbers is: %d", sum);

    return 0;
}
