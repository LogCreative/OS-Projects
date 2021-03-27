#include "buffer.h"

buffer_item buffer[BUFFER_SIZE];

int front = 0, rear = 0;

int insert_item(buffer_item item){
    if((rear+1) % BUFFER_SIZE == front) return -1;
    rear = (rear + 1) % BUFFER_SIZE;
    buffer[rear] = item;
    return 0;
}

int remove_item(buffer_item *item){
    if(front==rear) return -1;
    front = (front + 1) % BUFFER_SIZE;
    *item = buffer[front];
    return 0;
}