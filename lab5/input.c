#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int** input_matrix(int rows, int cols) {
	int **arr = (int **) malloc( rows * sizeof(int *) );
	int element;
	for(int i = 0; i < rows; ++i) {
		arr[i] = (int *) malloc( cols * sizeof(int) );
		
		for(int j=0; j<cols; ++j) {
			scanf("%d ", &element);
			arr[i][j] = element;
		}
	}

	return arr;
}

void print_matrix(int** arr, int rows, int cols) {
	for(int i = 0; i < rows; ++i) {
		
		for(int j=0; j < cols; ++j) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}	
}

int main() {

	int rows = 6;
	int cols = 8;

	int** m = input_matrix(rows, cols);
	print_matrix(m, rows, cols);

	return 0;
}