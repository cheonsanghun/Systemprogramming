#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    char buf[256];
    char *argv[50];
    int narg;
    pid_t pid;

    while(1){
        printf("shell>");
        fgets(buf, sizeof(buf), stdin);

        pid = fork();
        if (pid == 0)
            execvp(argv[0], argv);
        else if (pid > 0)
            wait(0);
        else
            perror("fork faild");
    }
    narg = getargs(buf, argv);
}

int getargs(char *cmd, char **argc)
{
    int narg = 0;

    while(*cmd){
        if(*cmd == ' ' || *cmd == '\t')
            *cmd++ = '\0';
        else{
            argv[narg++] = cmd++;
            while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
                cmd++;
            }
    }
    argv[narg] = NULL;
    return narg;
} 
