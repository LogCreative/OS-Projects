/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>

#include "task.h"

int clock = 0;

int tasknum = 0;

int turnaround = 0;
int waiting = 0;
int response = 0;

// run this task for the specified time slice
void run(Task *task, int slice) {

    if(task->exec==0){
        tasknum++;
        response += clock;
    }
    waiting += clock - task->exec;

    printf("Running task = [%s] [%d] [%d] for %d units.\n",task->name, task->priority, task->burst, slice);
    
    clock += slice; 
    task->burst -= slice;
    task->exec = clock;
    if(task->burst==0) turnaround += clock;

}

void printAvg(){
    printf("Task Num:\t%d\n", tasknum);
    printf("Turnaround Avg:\t%2f\n", (double) turnaround / tasknum);
    printf("Waiting Avg:\t%2f\n", (double) waiting / tasknum);
    printf("Response Avg:\t%2f\n", (double) response / tasknum);
}
