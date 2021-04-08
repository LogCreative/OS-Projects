#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 30
int MAX;

struct alloc
{
    int start;
    int size;
    char process[MAXLINE];
    struct alloc* next;
};

// List
struct alloc* space_head;

int request(char* process, int size, char* flag){
    struct alloc* tmp = space_head;
    struct alloc* select = NULL;
    int besthole;
    switch(flag[0]){
        case 'F':
            // First-fit
            while(tmp){
                if(strcmp(tmp->process,"Unused")==0 && tmp->size >= size){
                    select = tmp;
                    break;
                }
                tmp = tmp -> next;
            }
            break;
        case 'B':
            // Best-fit
            besthole = MAX;
            while(tmp){
                if(strcmp(tmp->process,"Unused")==0 && tmp->size >= size && tmp->size - size < besthole){
                    select = tmp;
                    besthole = tmp->size - size;
                }
                tmp = tmp->next;
            }
            break;
        case 'W':
            // Worst-fit
            besthole = -1;
            while(tmp){
                if(strcmp(tmp->process,"Unused")==0 && tmp->size >= size && tmp->size - size > besthole){
                    select = tmp;
                    besthole = tmp->size - size;
                }
                tmp = tmp -> next;
            }
            break;
    }
    if(!select) return 1;
    if(select->size > size){
        struct alloc* new_alloc = (struct alloc*) malloc(sizeof(struct alloc));
        new_alloc->start = select->start + size;
        new_alloc->size = select->size - size;
        strcpy(new_alloc->process,"Unused");
        new_alloc->next = select->next;
        
        select->size = size;
        strcpy(select->process, process);
        select->next = new_alloc;
    } else if (select->size == size){
        strcpy(select->process, process);
    }
    return 0;
}

int release(char *process){
    struct alloc* tmp = space_head;
    if(strcmp(tmp->process, process)==0){

        // X -> O
        // X X -> O X
        // X O -> O

        int after = (tmp->next ? strcmp(tmp->next->process,"Unused") == 0 : 0);

        if (after){
            space_head = tmp->next;
            space_head->start -= tmp->size;
            space_head->size += tmp->size;
        } else {
            strcpy(space_head->process, "Unused");
        }
        
        return 0;
    }
    while(tmp->next){
        if(strcmp(tmp->next->process,process)==0){
            struct alloc* del = tmp->next;

            // O X O -> O
            // X X O -> X O
            // O X X -> O X
            // X X X -> X O X
            
            int before = strcmp(tmp->process,"Unused") == 0;
            int after = (tmp->next->next ? strcmp(tmp->next->next->process,"Unused") == 0 : 0);

            if(before && after){
                tmp->size += del->size + tmp->next->next->size;
                tmp->next = tmp->next->next->next;
            } else if (after){
                tmp->next->next->start -= del->size;
                tmp->next->next->size += del->size;
                tmp->next = tmp->next->next;
            } else if (before){
                tmp->size += del->size;
                tmp->next = tmp->next->next;
            } else {
                strcpy(del->process,"Unused");
            }

            return 0;
        }
        tmp = tmp->next;
    }
    return 1;
}

void compat() {
    
    struct alloc* tail = space_head;
    int count = 1;
    while(tail->next){
        tail = tail->next;
        ++count;
    }

    // Move to tail
    // O O X X X -> O X X X O -> X X X O O
    // O X X X X -> X X X X O
    // X O X O X -> X X O X O -> X X X O O
    
    struct alloc* tmp = space_head;
    while (tmp->next && strcmp(tmp->process,"Unused")==0){
        space_head = tmp->next;

        struct alloc* ch_tmp = space_head;
        while(ch_tmp){
            ch_tmp->start -= tmp->size;
            ch_tmp = ch_tmp->next;
        }
        
        tmp->next = tail->next;
        tmp->start = tail->start + tail->size;
        tail->next = tmp;
        tail = tmp;
        tmp = space_head;
        --count;
        if(!count) break;
    }

    while(count) {
        if(!tmp->next) break;
        if(tmp->next->next && strcmp(tmp->next->process,"Unused")==0){
            struct alloc* mover = tmp->next;
            tmp->next = tmp->next->next;

            struct alloc* ch_tmp = tmp->next;
            while(ch_tmp){
                ch_tmp->start -= mover->size;
                ch_tmp = ch_tmp->next;
            }
            
            mover->next = tail->next;
            mover->start = tail->start + tail->size;
            tail->next = mover;
            tail = mover;
            --count;
        }
        tmp = tmp->next;
        --count;
    }

    // Compat the space
    while(tmp && tmp->next){
        tmp->size += tmp->next->size;
        tmp->next = tmp->next->next;
    }
}

void status() {
    struct alloc* tmp = space_head;
    while(tmp){
        char process_name[MAXLINE];
        if(strcmp(tmp->process,"Unused")==0) strcpy(process_name,"Unused");
        else { 
            strcpy(process_name, "Process ");
            strcat(process_name, tmp->process);
        };
        fprintf(stdout,"Addresses [%d:%d] %s\n", tmp->start, tmp->start + tmp->size - 1, process_name);
        tmp = tmp->next;
    }
}

int main(int argc, char* argv[]){
    // if(argc==1){
    //     fprintf(stderr, "Please assign the initial amount of memory.\n");
    //     return -1;
    // }
    // MAX = atoi(argv[1]);
    MAX = 1048576;

    space_head = (struct alloc*) malloc(sizeof(struct alloc));
    space_head->start = 0;
    space_head->size = MAX;
    strcpy(space_head->process,"Unused");
    space_head->next = NULL;

    char command[MAXLINE];
    do{
        fprintf(stdout, "allocator> ");
        fscanf(stdin, "%s", command);
        if(strcmp(command,"RQ")==0){
            char process[MAXLINE];
            int size;
            char flag[2];

            fscanf(stdin, "%s", process);
            fscanf(stdin, "%d", &size);
            fscanf(stdin, "%s", flag);

            if(request(process, size, flag))
                fprintf(stderr, "No sufficient memory!\n");
            
        } else if (strcmp(command,"RL")==0){
            char process[MAXLINE];
            fscanf(stdin, "%s", process);

            if(release(process))
                fprintf(stderr, "No such process to be released!\n");

        } else if (strcmp(command,"C")==0)
            compat();
        else if (strcmp(command,"STAT")==0) 
            status();
    } while(strcmp(command,"X")!=0);
}