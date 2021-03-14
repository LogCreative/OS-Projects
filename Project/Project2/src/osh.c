#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

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

        int flag = 0;

        if (strcmp(rline,"!!\n")==0){
            if(!buf[0]){
                fprintf(stdout, "%s\n", "No commands in history.");
                flag = -1;
            } else {
                memcpy(rline, buf, MAX_LINE*sizeof(char));
                fprintf(stdout, "%s", rline);
            }
        } else memcpy(buf, rline, MAX_LINE*sizeof(char));

        int fd = -1;
        int file_mode = -1;
        int file_arg = -1;

        int argc = 0;
        char prev = ' ';
        
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
                case '>':
                    file_mode = O_WRONLY;
                    args[argc++] = NULL;
                    prev = ' ';
                    file_arg = argc;
                    break;
                case '<':
                    file_mode = O_RDONLY;
                    args[argc++] = NULL;
                    prev = ' ';
                    file_arg = argc;
                    break;
                default:
                    if (prev == ' ') args[argc++] = rptr;
                    prev = *rptr;
                    break;
            }
        }

        if(flag == -1) continue;

        args[argc] = NULL;
        if (!args[0]) continue;
        should_run = strcmp(args[0],"exit");

        pid_t pid;
        pid = fork();

        if (pid < 0) fprintf(stderr, "Fork Failed"); 
        else if (pid == 0) {
            if(file_mode >= 0){
                fd = open(args[file_arg], file_mode, 0666);
                if(file_mode == O_WRONLY){
                    if(fd == -1) fd = creat(args[file_arg], 0666);
                    if(fd == -1) fprintf(stderr, "%s %s.\n", "Cannot write file", args[file_arg]);
                    else dup2(fd, STDOUT_FILENO);
                } else if (file_mode == O_RDONLY){
                    if(fd == -1) fprintf(stderr, "%s %s.\n", "Cannot read file",args[file_arg]);
                    else dup2(fd, STDIN_FILENO);
                }
            }
            execvp(args[0],args);
            if(fd != -1) close(fd);
            return 0;
        }
        else if (should_wait) wait(NULL);

    }

    return 0;
}