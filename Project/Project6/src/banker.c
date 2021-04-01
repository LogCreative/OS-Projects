#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBEROFCUSTOMERS 5
#define NUMBEROFRESOURCES 4
#define MAXLINE 1000

/* the available amount of each resource */
int available[NUMBEROFRESOURCES];

/*the maximum demand of each customer */
int maximum[NUMBEROFCUSTOMERS][NUMBEROFRESOURCES];

/* the amount currently allocated to each customer */
int allocation[NUMBEROFCUSTOMERS][NUMBEROFRESOURCES];

/* the remaining need of each customer */
int need[NUMBEROFCUSTOMERS][NUMBEROFRESOURCES];

int request_resources(int customer_num, int request[]){
    for(int j = 0; j < NUMBEROFRESOURCES; ++j){
        if(allocation[customer_num][j] + request[j] > maximum[customer_num][j]){
            fprintf(stderr, "RQ Err: Request limit exceeded.\n");
            return 1;
        }
        if(request[j]>available[j]){
            fprintf(stderr, "RQ Err: No available resources.\n");
            return 1;
        }
    }

    // Fake allocation
    int available_pre[NUMBEROFRESOURCES];
    for(int j = 0; j < NUMBEROFRESOURCES; ++j){
        allocation[customer_num][j] += request[j];
        need[customer_num][j] -= request[j];
        available_pre[j] = available[j] - request[j];
    }
    
    int finish[NUMBEROFCUSTOMERS];
    for(int i = 0; i < NUMBEROFCUSTOMERS; ++i){
        int finish_flag = 1;
        for(int j = 0; j < NUMBEROFRESOURCES; ++j)
            if(need[i][j] > 0)
                finish_flag = 0;
        finish[i] = finish_flag;
    }

    int found = 0;
    do {
        found = 0;
        fprintf(stdout, "Current Available: ");
        for(int j = 0; j < NUMBEROFRESOURCES; ++j)
            fprintf(stdout, "%d ", available_pre[j]);
        
        for(int i = 0; i < NUMBEROFCUSTOMERS; ++i){
            if(!finish[i]){
                int next = 1;
                for(int j = 0; j < NUMBEROFRESOURCES; ++j)
                    if(need[i][j] > available_pre[j]){
                        next = 0;
                        break;
                    }
                if(!next) continue;
                finish[i] = 1;
                for(int j = 0; j < NUMBEROFRESOURCES; ++j)
                    available_pre[j] += allocation[i][j];
                found = 1;
                fprintf(stdout, " > %d", i);
                break;
            }
        }

        fprintf(stdout, "\n");
    } while (found);

    int all_finish_flag = 1;
    for(int i = 0; i < NUMBEROFCUSTOMERS; ++i)
        if(!finish[i])
            all_finish_flag = 0;
    if(!all_finish_flag){
        // fallback
        for(int j = 0; j < NUMBEROFRESOURCES; ++j){
            allocation[customer_num][j] -= request[j];
            need[customer_num][j] += request[j];
        }
        fprintf(stderr, "RQ Err: Deadlock detected.\n");
        return 1;
    }

    for(int j = 0; j < NUMBEROFRESOURCES; ++j)
        available[j] -= request[j];
    return 0;
}

void release_resources(int customer_num, int release[]){
    int real_release[NUMBEROFRESOURCES];
    int warn_flag = 0;
    for(int j = 0; j < NUMBEROFRESOURCES; ++j){
        if(release[j] > allocation[customer_num][j]){
            real_release[j] = allocation[customer_num][j];
            warn_flag = 1;
        }
        else real_release[j] = release[j];
        allocation[customer_num][j] -= real_release[j];
        maximum[customer_num][j] -= real_release[j];
        available[j] += real_release[j];
    }
    if(warn_flag){
        fprintf(stderr, "RL Warn: Lack of allocation. Only RL ( ");
        for(int j = 0; j < NUMBEROFRESOURCES; ++j)
            fprintf(stdout, "%d ", real_release[j]);
        fprintf(stdout, ").\n");
    }
    int fin_flag = 1;
    for(int j = 0; j < NUMBEROFRESOURCES; ++j)
        if(maximum[customer_num][j]>0)
            fin_flag = 0;
    if(fin_flag)
        fprintf(stdout, "RL Info: Process %d is finished.\n", customer_num);
}

int main(int argc, char* argv[]){
    for(int i = 0; i< NUMBEROFRESOURCES; ++i)
        available[i] = atoi(argv[i+1]);
    
    FILE *in;
    char *temp;
    char customer[MAXLINE];

    in = fopen("info.txt","r");

    for(int i = 0; i<NUMBEROFCUSTOMERS; ++i){
        if(fgets(customer,MAXLINE,in)==NULL){
            fprintf(stderr,"Read file error!\n");
            return -1;
        }
        temp = strdup(customer);

        for(int j = 0; j<NUMBEROFRESOURCES; ++j){
            int maxres = atoi(strsep(&temp,","));
            need[i][j] = maxres;
            maximum[i][j] = maxres;
            allocation[i][j] = 0;
        }
        
        free(temp);
    }

    fclose(in);

    char command[2];
    fprintf(stdout,"> ");
    while(fscanf(stdin,"%s",command)!=EOF){
        if (strcmp(command,"RQ")==0){
            int customer_num;
            fscanf(stdin, "%d", &customer_num);
            int request[NUMBEROFRESOURCES];
            for(int j = 0; j < NUMBEROFRESOURCES; ++j)
                fscanf(stdin, "%d", &request[j]);
            if(request_resources(customer_num, request))
                fprintf(stdout, "RQ Denied.\n");
            else fprintf(stdout, "RQ Success.\n");
        } else if (strcmp(command,"RL")==0){
            int customer_num;
            fscanf(stdin, "%d", &customer_num);
            int release[NUMBEROFRESOURCES];
            for(int j = 0; j < NUMBEROFRESOURCES; ++j)
                fscanf(stdin, "%d", &release[j]);
            release_resources(customer_num, release);
            fprintf(stdout, "RL Complete.\n");
        } else if (strcmp(command,"*")==0){
            fprintf(stdout, "\t\t\t\tAvailable: \t");
            for(int j = 0; j<NUMBEROFRESOURCES; ++j)
                fprintf(stdout, "%d ", available[j]);
            fprintf(stdout, "\n");
            fprintf(stdout,"Process\t\tMaximum\t\tAllocation\tNeed\n");
            for(int i = 0; i < NUMBEROFCUSTOMERS; ++i){
                fprintf(stdout, "%d\t\t", i); 
                for(int j = 0; j < NUMBEROFRESOURCES; ++j)
                    fprintf(stdout, "%d ", maximum[i][j]);
                fprintf(stdout, "\t");
                for(int j = 0; j < NUMBEROFRESOURCES; ++j)
                    fprintf(stdout, "%d ", allocation[i][j]);
                fprintf(stdout, "\t");
                for(int j = 0; j < NUMBEROFRESOURCES; ++j)
                    fprintf(stdout, "%d ", need[i][j]);
                fprintf(stdout, "\n");
            }
        }
        fprintf(stdout,"> ");
    }

    return 0;
}