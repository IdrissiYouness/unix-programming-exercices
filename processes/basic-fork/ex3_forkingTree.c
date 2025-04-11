#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
  printf("je suis le processus pere de pid %d\n", getpid());

  pid_t pid1 = fork();
  if (pid1 == 0) { 
        printf("Processus fils 1 - PID: %d, PPID: %d\n", getpid(), getppid());

        pid_t pid3 = fork();
        if (pid3 == 0) {
            printf("Petit-fils (1.1) - PID: %d, PPID: %d\n", getpid(), getppid());
        } else {
            pid_t pid4 = fork();
            if (pid4 == 0) {
                printf("Petit-fils (1.2) - PID: %d, PPID: %d\n", getpid(), getppid());
            } else {
                wait(NULL);
                wait(NULL);
            }
        }
        exit(0);
  } else {
        pid_t pid2 = fork();
        if (pid2 == 0) { 
            printf("Processus fils 2 - PID: %d, PPID: %d\n", getpid(), getppid());
            
            pid_t pid5 = fork();
            if (pid5 == 0) {
                printf("Petit-fils (2.1) - PID: %d, PPID: %d\n", getpid(), getppid());
                pid_t pid6 = fork();
                if (pid6 == 0) {
                   printf("Petit-fils (2.1.1) - PID: %d, PPID: %d\n", getpid(), getppid());
                  
                }else {
                  wait(NULL);
                }
            } else {
                                
                /*
                pid_t pid6 = fork();
                if (pid6 == 0) {
                    printf("Petit-fils (2.2) - PID: %d, PPID: %d\n", getpid(), getppid());
                } else {
                    pid_t pid7 = fork();
                    if (pid7 == 0) {
                        printf("Petit-fils (2.3) - PID: %d, PPID: %d\n", getpid(), getppid());
                    } else {
                        wait(NULL);
                        wait(NULL);
                        wait(NULL);
                    }
                }
                */         
                
                wait(NULL);
            }
            exit(0);
        } else {
            wait(NULL);
            wait(NULL);
        }
  }

  return 0; 
}
