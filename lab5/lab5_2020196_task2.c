#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int search(int array[], int x, int low, int high)
{
	if (high >= low)
	{
		int mid = low + (high - low) / 2;

		if (array[mid] == x)
		{
			return mid;
		}

		int left, right;

#pragma omp task shared(left)
		left = search(array, x, low, mid - 1);

#pragma omp task shared(right)
		right = search(array, x, mid + 1, high);

#pragma omp taskwait
		if (left != -1)
		{
			return left;
		}
		if (right != -1)
		{
			return right;
		}
	}
	return -1;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Incorrect Argument Structure!\n");
		printf("%s <arraySize> <numSearch> <numThreads>\n", argv[0]);
		exit(1);
	}

	int arraySize = atoi(argv[1]);
	int numToSearch = atoi(argv[2]);
	int numThreads = atoi(argv[3]);

	int *arr = malloc(arraySize * sizeof(int));

	printf("Generatating an array of size %d\n", arraySize);
#pragma omp parallel for num_threads(numThreads)
	for (int i = 0; i < arraySize; i++)
	{
		arr[i] = rand() % 100;
	}

	printf("\n");
	for (int i = 0; i < arraySize; i++)
	{
		printf("Array[%d]: %d\n", i, arr[i]);
	}
	printf("\n\n");

	printf("Sorting The Array!\n");

	int swapped;
	for (int i = 0; i < arraySize - 1; i++)
	{
		swapped = 0;
		for (int j = 0; j < arraySize - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = 1;
			}
		}
		if (swapped == 0)
		{
			break;
		}
	}

	printf("\n");
	for (int i = 0; i < arraySize; i++)
	{
		printf("Array[%d]: %d\n", i, arr[i]);
	}
	printf("\n\n");

	printf("Searching for the number %d...\n", numToSearch);
	int result;

#pragma omp parallel num_threads(numThreads)
	{
#pragma omp single
		{
			result = search(arr, numToSearch, 0, arraySize);
		}
	}

	if (result == -1)
	{
		printf("Number %d is not in array!\n", numToSearch);
	}
	else
	{
		printf("Number %d found At index: %d\n", numToSearch, result);
	}

	free(arr);
	return 0;
}