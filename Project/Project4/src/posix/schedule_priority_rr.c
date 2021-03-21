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
        while(temp->next && temp->task->priority >= newTask->priority) temp = temp->next;
        insert(&temp->next,newTask);
    }

}

void schedule(){
    struct node *pivot = taskList;
    while(pivot){
        Task* thisTask = pivot->task;
        int slice = thisTask->burst>QUANTUM? QUANTUM : thisTask->burst;
        run(thisTask, slice);
        thisTask->burst -= slice;
        
        delete(&taskList, thisTask);
        if(thisTask->burst > 0){
            struct node* temp = taskList;
            while(temp->next && temp->task->priority>= thisTask->priority) temp = temp->next;
            if(temp) insert(&temp->next,thisTask);
            else{
                taskList = malloc(sizeof(struct node));
                taskList->task = thisTask;
                taskList->next = NULL; 
            }
        }
        pivot = pivot->next;
    }
}