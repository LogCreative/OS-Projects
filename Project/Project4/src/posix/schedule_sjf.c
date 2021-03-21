#include "schedulers.h"
#include "list.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

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
        while(temp->next) temp = temp->next;
        insert(&temp->next,newTask);
    }

}

void schedule(){
    while(taskList){
        struct node *minNode = taskList;

        struct node *pivot = taskList;
        while(pivot){
            if(pivot->task->burst<minNode->task->burst)
                minNode = pivot;
            pivot = pivot->next;
        }

        Task* thisTask = minNode->task;
        run(thisTask,thisTask->burst);
        delete(&taskList, thisTask);
    }
}