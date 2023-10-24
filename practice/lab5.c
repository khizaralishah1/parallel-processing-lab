#include <stdio.h>
#include <omp.h>

int sum( int x ) {
    return x + 2;
}

int product ( int x ) {
    return x * 2;
}

int sub( int x ) {
    return x - 2;
}

int main(int argc, char* argv[]) {

    int x;
    scanf("%d", &x);

    #pragma omp parallel sections nums_threads(6)
    {
        #pragma omp section
            printf("%d\n", sum(x));

        #pragma omp section
            printf("%d\n", product(x));

        #pragma omp section
            printf("%d\n", sub(x));
    }

    return 0;
}

