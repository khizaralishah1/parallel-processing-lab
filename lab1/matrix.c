#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		dprintf(2, "Error! Must have 3 args\n");
		exit(-1);
	}

	size_t size_a = atoi(argv[1]);
	size_t size_b = atoi(argv[2]);

	printf("Given matrices size:\nA: %zu\nB: %zu\n", size_a, size_b);

	int** matrix_a = (int**) malloc( sizeof(int) * size_a );
	int** matrix_b = (int**) malloc( sizeof(int) * size_b );

	if (!matrix_a || !matrix_b) {
		dprintf(2, "Error! Memory allocation failed\n");
		exit(-1);
	}

	int elem;

	printf("Enter matrix A elements:\n");

	for(size_t i = 0; i < size_a; ++i) {
		matrix_a[i] = (int*) malloc( sizeof(int) * size_a );
		
		for(size_t j = 0; j < size_a; ++j) {
			scanf("%d", &elem);
			matrix_a[i][j] = elem;
		}
	}

	printf("Enter matrix B elements:\n");
	
	for(size_t i = 0; i < size_b; ++i) {
		matrix_b[i] = (int*) malloc( sizeof(int) * size_b );
	
		for(size_t j = 0; j < size_b; ++j) {
			scanf("%d", &elem);
			matrix_b[i][j] = elem;
		}
	}

	size_t small_size = size_a < size_b ? size_a : size_b;
	
	int** result = (int**) malloc( sizeof(int) * small_size );

	int diff = 0;

	printf("Sum: C = A + B\n");

	printf("Matrix C:\n");
	for(size_t i = 0; i < small_size; ++i) {
		result[i] = (int*) malloc( sizeof(int) * small_size );
		
		for(size_t j = 0; j < small_size; ++j) {
			result[i][j] += matrix_a[i][j] + matrix_b[i][j];
			printf("%d ", result[i][j]);
			diff -= result[i][j];
		}
		printf("\n");
	}

	printf("\n\nDifference of elements of C = %d\n", diff);
	
	return 0;
}	
