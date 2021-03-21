#include "schedulers.h"
#include "list.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

struct node* taskList = NULL;
int value = 0;

void add(char *name, int priority, int burst){
    Task* newTask = (Task*) malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = __sync_fetch_and_add(&value,1);
    newTask->exec = 0;

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
    
    // traverse(taskList);

    struct node *temp = taskList;
    while(temp){
        Task* thisTask = temp->task;
        run(thisTask,thisTask->burst);
        delete(&taskList, thisTask);
        temp = temp->next;
    }
}