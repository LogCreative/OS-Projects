#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

#define TRUE 1

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

void buffer_init(){
    pthread_mutex_init(&mutex,NULL);
    sem_init(&empty, 0, BUFFER_SIZE - 1);
    sem_init(&full, 0, 0);
}

void *producer(void *param){
    buffer_item item;

    while(TRUE){
        sleep(1);
        item = rand();
        
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        
        int error = 0;

        if(insert_item(item)){
            fprintf(stderr,"FULL!\n");
            error = 1;
        }
        else
            fprintf(stdout,"producer produced %d\n", item);

        pthread_mutex_unlock(&mutex);
        if(!error) sem_post(&full);
    }
}

void *consumer(void *param){
    buffer_item item;

    while(TRUE){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        int error = 0;
        if(remove_item(&item)){
            fprintf(stderr, "EMPTY!\n");
            error = 1;
        }
        else
            fprintf(stdout, "consumer consumed %d\n", item);

        pthread_mutex_unlock(&mutex);
        if(!error) sem_post(&empty);

        sleep(1);
    }
}

int main(int argc, char *argv[]){
    if(argc!=4){
        fprintf(stderr,"Three parameters are required!\n");
        return 1;
    }

    int sleep_amount = atoi(argv[1]);
    int p_count = atoi(argv[2]);
    int c_count = atoi(argv[3]);

    buffer_init();

    pthread_t* pbee = (pthread_t *) malloc(p_count*(sizeof(pthread_t)));
    for(int i = 0; i < p_count; ++i)
        pthread_create(&pbee[i], NULL, producer, NULL);
    
    pthread_t* cbee = (pthread_t *) malloc(c_count*(sizeof(pthread_t)));
    for(int j = 0; j < c_count; ++j)
        pthread_create(&cbee[j], NULL, consumer, NULL);
    
    sleep(sleep_amount);

    return 0;
}