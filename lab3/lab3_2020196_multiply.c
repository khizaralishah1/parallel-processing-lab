// Matrix Multiplication - 2020196 Khizar Ali Shah Lab 3

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char const *argv[])
{

	int rows, cols;

	if (argc < 3)
	{
		printf("No enough arguments\n");
	}

	printf("%s\n", argv[0]);

	rows = atoi(argv[1]);
	cols = atoi(argv[2]);

	int **matrix1;

	matrix1 = (int **)malloc(rows * sizeof(int));

	for (int i = 0; i < cols; i++)
	{
		matrix1[i] = (int *)malloc(cols * sizeof(int));
	}

	printf("Enter elements of matrix1.\n");

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			scanf("%d", &matrix1[i][j]);
		}
		printf("\n");
	}

	int **matrix2;

	matrix2 = (int **)malloc(rows * sizeof(int *));

	for (int i = 0; i < rows; i++)
	{
		matrix2[i] = (int *)malloc(cols * sizeof(int));
	}

	printf("Enter elements of matrix2.\n");

#pragma omp parallel for
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			scanf("%d", &matrix2[i][j]);
		}
		printf("\n");
	}

	int **matrixResult;

	matrixResult = (int **)malloc(rows * sizeof(int));

	for (int i = 0; i < rows; i++)
	{
		matrixResult[i] = (int *)malloc(cols * sizeof(int));
	}

#pragma omp parallel for
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrixResult[i][j] = 0;
			for (int k = 0; k < cols; k++)
			{
				matrixResult[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}

	printf("Resultant matrix is: \n");

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%d ", matrixResult[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < rows; i++)
	{
		free(matrix1[i]);
		free(matrix2[i]);
		free(matrixResult[i]);
	}

	free(matrix1);
	free(matrix2);
	free(matrixResult);

	return 0;
}