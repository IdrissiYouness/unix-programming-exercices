#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid1, pid2, pid3;
  int status;

  pid1 = fork();
  if (pid1 == 0) {
    pid2 = fork();
    if (pid2 == 0) {
      pid3 = fork();
      if (pid3 == 0) {
        printf("troisième affichage \n");
        exit(3);
      } else {
        waitpid(pid3, &status, 0);
        printf("deuxième affichage \n");
        exit(2);
      }
    } else {
      waitpid(pid2, &status, 0);
      printf("premier affichage \n");
      exit(1);
    }
  } else {
    printf("quatrième affichage \n");

    waitpid(pid1, &status, 0);
  }
}
