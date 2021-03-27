/**
 * Implementation of thread pool.
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "threadpool.h"

#define QUEUE_SIZE 10
#define NUMBER_OF_THREADS 3

#define TRUE 1

// this represents work that has to be 
// completed by a thread in the pool
typedef struct 
{
    void (*function)(void *p);
    void *data;
}
task;

// the work queue
task workqueue[QUEUE_SIZE];

int front = 0, rear = 0;

// the worker bee
pthread_t bee[NUMBER_OF_THREADS];

// mutex
pthread_mutex_t queue_mutex;

// semaphore
sem_t sem_submit;

// insert a task into the queue
// returns 0 if successful or 1 otherwise, 
int enqueue(task t) 
{

    pthread_mutex_lock(&queue_mutex);

    int res = 0;
    if((rear + 1) % QUEUE_SIZE == front) res = 1;
    else {
        rear = (rear + 1) % QUEUE_SIZE;
        workqueue[rear] = t;
    }

    pthread_mutex_unlock(&queue_mutex);
    
    return res;
}

// remove a task from the queue
task dequeue() 
{

    pthread_mutex_lock(&queue_mutex);

    front = (front + 1) % QUEUE_SIZE;
    task taskfront = workqueue[front];

    pthread_mutex_unlock(&queue_mutex);

    return taskfront;
}

// the worker thread in the thread pool
void *worker(void *param)
{
    while(TRUE){
        sem_wait(&sem_submit);
        // execute the task
        task worktodo = dequeue();
        execute(worktodo.function, worktodo.data);
    }

    pthread_exit(0);
}

/**
 * Executes the task provided to the thread pool
 */
void execute(void (*somefunction)(void *p), void *p)
{
    (*somefunction)(p);
}

/**
 * Submits work to the pool.
 */
int pool_submit(void (*somefunction)(void *p), void *p)
{
    task worktodo;
    worktodo.function = somefunction;
    worktodo.data = p;
    int res = enqueue(worktodo);
    if (!res) sem_post(&sem_submit);
    return res;
}

// initialize the thread pool
void pool_init(void)
{
    // mutual-exclusion locks
    pthread_mutex_init(&queue_mutex, NULL);

    // semaphores
    sem_init(&sem_submit, 0, 0);

    for(int i = 0; i < NUMBER_OF_THREADS; ++i)
        pthread_create(&bee[i],NULL,worker,NULL);
}

// shutdown the thread pool
void pool_shutdown(void)
{
    for(int i = 0; i < NUMBER_OF_THREADS; ++i)
        pthread_cancel(bee[i]);
    for(int i = 0; i < NUMBER_OF_THREADS; ++i)
        pthread_join(bee[i],NULL);
}
