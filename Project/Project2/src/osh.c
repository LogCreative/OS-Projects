#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80

int main(void){
    char *args[MAX_LINE/2 + 1];
    int should_run = 1;

    char buf[MAX_LINE] = "\0";

    while (should_run) {
        printf("osh>");
        fflush(stdout);

        int should_wait = 1;
        char rline[MAX_LINE];
        fgets(rline, MAX_LINE, stdin);

        int argc = 0;
        char prev = ' ';
        int flag = 0;
        for(char* rptr = rline; rptr < rline + MAX_LINE && !flag; ++rptr){
            switch (*rptr) {
                case '&':
                    should_wait = 0;
                case '\n':
                    flag = 1;
                case ' ':
                    prev = *rptr;
                    *rptr = '\0';
                    break;
                case '!':
                    if (prev=='!' && argc == 0){
                        if(!buf[0]){
                            fprintf(stdout, "%s\n", "No commands in history.");
                            flag = -1;
                        } else {
                            // strcpy(rline, buf);
                            memcpy(rline, buf, MAX_LINE*sizeof(char));
                            fprintf(stdout, "%s\n", rline);
                            flag = 2;
                        }
                    }
                    prev = *rptr;
                    break;
                case '\0':
                    flag = -2;
                    break;
                default:
                    if (prev == ' ') args[argc++] = rptr;
                    prev = *rptr;
                    break;
            }
        }

        switch(flag){
            case 1:
                args[argc] = NULL;
            case 2:
                if (!args[0]) break;
                // strcpy(buf, rline);
                memcpy(buf, rline, MAX_LINE*sizeof(char));
                should_run = strcmp(args[0],"exit");

                pid_t pid;
                pid = fork();

                if (pid < 0) fprintf(stderr, "Fork Failed"); 
                else if (pid == 0) return execvp(args[0],args);
                else if (should_wait) wait(NULL);
                break;
        }

    }

    return 0;
}