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
    // 0 if successful
    // 1 if unsuccessful
    return 0;
}

void release_resources(int customer_num, int release[]){

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
    while(fscanf(stdin,"%s",command)!=EOF){
        if (strcmp(command,"RQ")==0){
            int customer_num;
            fscanf(stdin, "%d", &customer_num);
            int request[NUMBEROFRESOURCES];
            for(int j = 0; j < NUMBEROFRESOURCES; ++j)
                fscanf(stdin, "%d", &request[j]);
            if(request_resources(customer_num, request))
                fprintf(stdout, "RQ Failed.\n");
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
    }

    return 0;
}