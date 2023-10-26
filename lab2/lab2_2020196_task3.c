// Khizar Ali Shah - 2020196 Lab 2 Task 3
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int BUFFER_SIZE;
int NUM_PRODUCERS;
int NUM_CONSUMERS;

// create a lock that provides syncronization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int *array;
int count = 0;

void *producer(void *arg)
{
    // retrieve the thread number
    int thread_no = *((int *)arg);
    while (1)
    {

        sleep(1);

        int part = rand() % 100;

        pthread_mutex_lock(&mutex);

        if (count < BUFFER_SIZE)
        {
            array[count] = part;
            printf("Producer %d supplied part: %d\n", thread_no, part);
            count++;
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// threaded function for the consumer thread
void *consumer(void *arg)
{
    // get the thread number
    int thread_no = *((int *)arg);
    while (1)
    {

        sleep(1);
        pthread_mutex_lock(&mutex);
        // if there are 3 parts in the buffer, assemble the car
        if (count >= 3)
        {
            printf("Consumer %d assembled a car with parts: %d, %d, %d\n", thread_no, array[count - 3], array[count - 2], array[count - 1]);
            // decrease the buffer size by 3
            count -= 3;
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        printf("Please provide arguments in the form:\n");
        printf("%s <buffer_size> <num_producers> <num_consumers>", argv[0]);
        return 1;
    }

    BUFFER_SIZE = atoi(argv[1]);
    NUM_PRODUCERS = atoi(argv[2]);
    NUM_CONSUMERS = atoi(argv[3]);

    // allocate memory for the buffer
    array = (int *)malloc(BUFFER_SIZE * sizeof(int));

    // create the consumer and producer threads
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        int *producer_no = malloc(sizeof(int));
        *producer_no = i;
        pthread_create(&producers[i], NULL, producer, producer_no);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        int *comsumer_no = malloc(sizeof(int));
        *comsumer_no = i;
        pthread_create(&consumers[i], NULL, consumer, comsumer_no);
    }

    // wait for both threads to finish
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_join(consumers[i], NULL);
    }

    // destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}