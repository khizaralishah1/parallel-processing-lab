// Khizar Ali Shah - 2020196 Lab 2 Task 1
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct array_data
{
    int *arr;
    int thread_num;
    int arr_size;
    int num_threads;
    int key;
} array_data;

// thread function that finds the key if present
void *thread_function(void *arg)
{
    // cast the argumennt to the struct
    array_data *temp = (array_data *)arg;
    // retrieve the thread number
    int n = temp->thread_num;

    // calculate the start and end for the threads
    int start = (n * temp->arr_size) / temp->num_threads;
    int end = ((n + 1) * temp->arr_size) / temp->num_threads;

    // iterate over the subarray
    for (int i = start; i < end; ++i)
    {
        // if key is found print and terminate
        if (temp->arr[i] == temp->key)
        {
            printf("Element Found At Index: %d\n", i);
            pthread_exit(NULL);
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

    struct timespec start_sq, end_sq;
    struct timespec start_par, end_par;

    // check if arguments provided are correct
    if (argc != 4)
    {
        printf("Usage: %s <array_size> <num_threads> <key>\n", argv[0]);
        return 1;
    }

    int array_size = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    int key = atoi(argv[3]);

    // check if number of threads and array size are correctly divisible
    if (array_size % num_threads != 0)
    {
        printf("Array size and number of threads must be divisible.\n");
        return 1;
    }

    printf("*************************** PARALLEL PROGRAM ***************************\n\n");

    // initialize the array
    int *array = (int *)malloc(sizeof(int) * array_size);
    for (int i = 0; i < array_size; ++i)
    {
        array[i] = i + 1;
    }

    pthread_t threads[num_threads];
    array_data thread_data[num_threads];

    clock_gettime(CLOCK_MONOTONIC, &start_par);

    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].thread_num = i;
        thread_data[i].arr = array;
        thread_data[i].arr_size = array_size;
        thread_data[i].num_threads = num_threads;
        thread_data[i].key = key;
        pthread_create(&threads[i], NULL, thread_function, &thread_data[i]);
    }

    // wait for the threads
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_par);

    double elapsed_time_threaded = (end_par.tv_sec - start_par.tv_sec) + (end_par.tv_nsec - start_par.tv_nsec) / 1e9;
    printf("Time taken for threaded module: %lf seconds\n", elapsed_time_threaded);

    printf("\n\n*************************** SEUQENTIAL PROGRAM ***************************\n");
    clock_gettime(CLOCK_MONOTONIC, &start_sq);
    for (int i = 0; i < array_size; i++)
    {
        if (array[i] == key)
        {
            printf("Element Found At Index: %d\n", i);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_sq);
    double elapsed_time_seq = (end_sq.tv_sec - start_sq.tv_sec) + (end_sq.tv_nsec - start_sq.tv_nsec) / 1e9;
    printf("Time taken for sequential module: %lf seconds\n", elapsed_time_seq);

    return 0;
}