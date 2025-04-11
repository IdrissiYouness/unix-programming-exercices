
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    
    pid_t pid;
    for (int i = 0; i < 10; i++) {
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork failed\n");
            exit(-1);
        }
        else if (pid == 0) {
            printf("Child process %d My process id : %d\n",i+1,getpid());
            printf("My Parent process id : %d\n",getppid());
            break;          
        }else{
            //printf("Parent process My process id : %d \n",getpid());
            //printf("My process id : %d\n",getpid());
            //exit(0);
            wait(0);
        }
    }
    
    /*
    for (int i = 0; i<10; i++) {
        if (fork() == 0) {
            printf("Child process %d\n",i+1);
            printf("My process id : %d\n",getpid());
            printf("My Parent process id : %d\n\n",getppid());
            exit(0);
        } 
    }
    */


}
