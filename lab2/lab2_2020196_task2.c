// Khizar Ali Shah - 2020196 Lab 2 Task 2
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// initialize the global variables
int **mat;
int mat_size;
int NUM_THREADS;
int *value_records;

// threaded function that finds the max in the 2D array
void* max_function(void* args){
    int thread_id = *((int*)args);
    // split the rows among the different threads
    int start_row = (mat_size / NUM_THREADS) * thread_id;
    int end_row = (thread_id == NUM_THREADS - 1) ? mat_size :start_row + (mat_size / NUM_THREADS);

    printf("Thread No %d, Start Row %d, End Row %d\n", thread_id, start_row, end_row);

    // find the max value in the selected rows
    int max = mat[start_row][0];
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < mat_size; j++) {
            if(i == start_row && j == 0){
                continue;
            }
            if(mat[i][j] > max){
                max = mat[i][j];
            }
        }
    }

    // save the max value in a array
    value_records[thread_id] = max;

    pthread_exit(NULL);

    return NULL;
}

// the same as max_function just reverse the operand
void* min_function(void* args){
    int thread_id = *((int*)args);
    int start_row = (mat_size / NUM_THREADS) * thread_id;
    int end_row = (thread_id == NUM_THREADS - 1) ? mat_size :start_row + (mat_size / NUM_THREADS);

    printf("Thread No %d, Start Row %d, End Row %d\n", thread_id, start_row, end_row);


    int min = mat[start_row][0];
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < mat_size; j++) {
            if(i == start_row && j == 0){
                continue;
            }
            if(mat[i][j] < min){
                min = mat[i][j];
            }
        }    }

    value_records[thread_id] = min;

    pthread_exit(NULL);

    return NULL;
}


int main(int argc, char *argv[]){

    // check for corrent number of arguments
    if(argc != 4){
        printf("Usage: %s <mat_size> <num_threads> <max_min>\n", argv[0]);
        return 1;
    }

    struct timespec start_sq, end_sq;
    struct timespec start_par, end_par;



    mat_size = atoi(argv[1]);
    NUM_THREADS = atoi(argv[2]);
    int max_min = atoi(argv[3]);

    // dynamically allocate memory for a 2D array
    mat = (int **)malloc(mat_size * sizeof(int *));
    for (int i = 0; i < mat_size; i++) {
        mat[i] = (int *)malloc(mat_size * sizeof(int));
    }

    value_records = (int*)malloc(NUM_THREADS*sizeof(int));

    // initialize the 2D array with values from 0 - 100
    for (int i = 0; i < mat_size; i++) {
        for (int j = 0; j < mat_size; j++) {
            mat[i][j] = rand() % 100;
        }
    }

    // display the elements in the matrix
    printf("*********** Matrix Elements ***********\n");
    for (int i = 0; i < mat_size; i++) {
        for (int j = 0; j < mat_size; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    clock_gettime(CLOCK_MONOTONIC, &start_par);
    printf("\n\n*************************** PARALLEL PROGRAM ***************************\n\n");

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    // bind the threads to the function
    printf("\n\n*********** Thread Details ***********\n");
    if(max_min == 0){
        for (int i = 0; i < NUM_THREADS; i++) {
            thread_ids[i] = i;
            pthread_create(&threads[i], NULL, max_function, &thread_ids[i]);
        }        
    }
    else if(max_min == 1){
        for (int i = 0; i < NUM_THREADS; i++) {
            thread_ids[i] = i;
            pthread_create(&threads[i], NULL, min_function, &thread_ids[i]);
        }      
    }

    // wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // get the max or min value from the values found by inidividual threads
    if(max_min == 0){
        int max = value_records[0];
        for (int i = 1; i < NUM_THREADS; i++) {
            if(value_records[i] > max){
                max = value_records[i];
            }
        }
        printf("\n\nMax Value: %d\n", max);
    }
    else if(max_min == 1){
        int min = value_records[0];
        for (int i = 1; i < NUM_THREADS; i++) {
            if(value_records[i] < min){
                min = value_records[i];
            }
        }
        printf("\n\nMin Value: %d\n", min);        
    }

    clock_gettime(CLOCK_MONOTONIC, &end_par);

    double elapsed_time_threaded = (end_par.tv_sec - start_par.tv_sec)+ (end_par.tv_nsec - start_par.tv_nsec) / 1e9;

    printf("Time taken for threaded module: %lf seconds\n", elapsed_time_threaded);


    // sequential code in which we just iterate using 2 for loops to find max or min element
    printf("\n\n*************************** SEUQENTIAL PROGRAM ***************************\n");
    clock_gettime(CLOCK_MONOTONIC, &start_sq);

    if(max_min == 0){
        int max = mat[0][0];
        for (int i = 0; i < mat_size; i++) {
            for(int j = 0; j < mat_size; j++){
                if(mat[i][j] > max){
                    max = mat[i][j];
                }
            }
        }
        printf("\nMax Value: %d\n", max);
    }
    else if(max_min == 1){
        int min = mat[0][0];
        for (int i = 0; i < mat_size; i++) {
            for(int j = 0; j < mat_size; j++){
                if(mat[i][j] < min){
                    min = mat[i][j];
                }
            }
        }
        printf("\nMin Value: %d\n", min);      
    }

    clock_gettime(CLOCK_MONOTONIC, &end_sq);

    double elapsed_time_seq = (end_sq.tv_sec - start_sq.tv_sec)+ (end_sq.tv_nsec - start_sq.tv_nsec) / 1e9;

    printf("Time taken for sequential module: %lf seconds\n", elapsed_time_seq);

    
    return 0;
}