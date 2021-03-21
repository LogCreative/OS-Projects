#include "schedulers.h"
#include "list.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

int value = 0;
struct node* taskList = NULL;

void add(char *name, int priority, int burst){
    Task* newTask = (Task*) malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = __sync_fetch_and_add(&value,1);
    newTask->exec = 0;

    addTask(newTask);
}

void addTask(Task* newTask){
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
}

void schedule(){
    struct node *pivot = taskList;
    while(pivot){
        Task* thisTask = pivot->task;
        int slice = thisTask->burst>QUANTUM? QUANTUM : thisTask->burst;
        run(thisTask, slice);
        
        delete(&taskList, thisTask);
        if(thisTask->burst > 0)
            addTask(thisTask);
        pivot = pivot->next;
    }
}