
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void binary_search(int*arr, int low, int high, int key, int mid)
{
	while (low <= high) {
		if(arr[mid] < key)
			low = mid + 1;
		else if (arr[mid] == key) {
			printf("%d found at location %d.n", key, mid+1);
			break;
		}
		else
			high = mid - 1;
		mid = (low + high)/2;
	}
}

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		printf("No enough arguments\n");
	}

	int low, high, mid;
	

	int size = atoi(argv[1]);
	int key = atoi(argv[2]);
	int noOfThreads = atoi(argv[3]);

	int arr[size];


	for(int i=0;i<size;i++)
	{
     	arr[i]=rand()%100;
	}

	printf("Generating array of size %d...\n\n", size);
	printf("Array is: \n[");

	for(int i = 0; i<size; i++)
	{
		printf("%d, ", arr[i]);
	}
	printf("\n\n");


	low = 0;
	high = size - 1;
	mid = (low+high)/2;
	
	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				binary_search(arr, low, high, key, mid);
			}
		}
	}
		

	if(low > high)
		printf("Not found! %d isn't present in the list.n", key);

	return 0;
}