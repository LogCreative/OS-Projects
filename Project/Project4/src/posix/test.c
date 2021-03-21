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

struct node* taskList = NULL;

void add(char *name, int priority, int burst){
    Task* newTask = (Task*) malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;

    if(!taskList){
        taskList = malloc(sizeof(struct node));
        taskList->task = newTask;
        taskList->next = NULL;
    } else {
        struct node* temp = taskList;
        while(temp->next && temp->next->task->priority >= newTask->priority)
            temp = temp->next;

        if(temp == taskList && temp->task->priority < newTask->priority){
            taskList = malloc(sizeof(struct node));
            taskList->task = newTask;
            taskList->next = temp;
        }
        else if(!temp->next){
            struct node* newNode = malloc(sizeof(struct node));
            newNode->task = newTask;
            newNode->next = NULL;
            temp->next = newNode;
        }
        else insert(&temp->next,newTask);
    }

    traverse(taskList);
    printf("\n");
}

int main(){
    Task* oldTask = (Task*) malloc(sizeof(Task));
    oldTask->name = "1";
    oldTask->priority = 4;
    oldTask->burst = 10;
    add(oldTask->name,oldTask->priority,oldTask->burst);

    Task* newTask = (Task*) malloc(sizeof(Task));
    newTask->name = "2";
    newTask->priority = 3;
    newTask->burst = 10;
    add(newTask->name,newTask->priority,newTask->burst);

    newTask = (Task*) malloc(sizeof(Task));
    newTask->name = "3";
    newTask->priority = 3;
    newTask->burst = 10;
    add(newTask->name,newTask->priority,newTask->burst);

    newTask = (Task*) malloc(sizeof(Task));
    newTask->name = "4";
    newTask->priority = 5;
    newTask->burst = 10;
    add(newTask->name,newTask->priority,newTask->burst);

    newTask = (Task*) malloc(sizeof(Task));
    newTask->name = "5";
    newTask->priority = 5;
    newTask->burst = 10;
    add(newTask->name,newTask->priority,newTask->burst);

    return 0;
}