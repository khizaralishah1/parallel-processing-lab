#include <stdio.h>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		dprintf(2, "Error! Must have 3 args\n");
		exit(-1);
	}

	size_t size = atoi(argv[1]);
	char op = argv[2];

	printf("Given array size: %d\n%Operator: %c\n", size, op);

	int* array = (int*) malloc( sizeof(int) * size);

	printf("Enter array elements:\n");

	int elem;

	for(size_t i = 0; i < size; ++i) {
		scanf("%d\n", elem);		
		array[i] = elem;
	}

	int result = array[0];

	for(size_t i = 1; i < size; ++i) {
		if (op == '+') {
			result += array[i];
		}
		else if(op == '-') {
			result -= array[i];
		}
		else if(op == '*') {
			result *= array[i];
		}
		else if(op == '/') {
			result /= array[i];
		}
	}

	printf("%c of all elements of array is: %d", op, result);

	return 0;
}	
