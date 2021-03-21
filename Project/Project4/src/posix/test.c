#include <stdio.h>
#include <stdlib.h>
#include "task.h"

struct node {
    Task *task;
    struct node *next;
};

// add a new task to the list of tasks
void insert(struct node **head, Task *newTask) {
    // add the new task to the list 
    struct node *newNode = malloc(sizeof(struct node));

    newNode->task = newTask;
    newNode->next = *head;
    *head = newNode;
}

// delete the selected task from the list
void delete(struct node **head, Task *task) {
    struct node *temp;
    struct node *prev;

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name,temp->task->name) == 0) {
        *head = (*head)->next;
    }
    else {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name,temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
}

// traverse the list
void traverse(struct node *head) {
    struct node *temp;
    temp = head;

    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}


int main(){
    struct node* taskList = malloc(sizeof(struct node));
    Task* oldTask = (Task*) malloc(sizeof(Task));
    oldTask->name = "1";
    taskList->task = oldTask;
    taskList->next = NULL;
    Task* newTask = (Task*) malloc(sizeof(Task));
    newTask->name = "2";
    insert(&taskList->next,newTask);

    return 0;
}