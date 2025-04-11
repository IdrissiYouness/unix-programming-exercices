#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  pid_t pid;
  for (int i = 0; i < 3; i++) {
    pid = fork();
    if (pid < 0) {
      fprintf(stderr, "Fork failed\n");
      exit(-1);
    } else if (pid == 0) {
      printf("Child process %d My process id : %d ", i + 1, getpid());
      printf(" My Parent process id : %d\n", getppid());
      // execl("/bin/ps", "ps", "-f", NULL);
      sleep(2);
      exit(0);
    }
  }

  sleep(1);
  execl("/bin/ps", "ps", "-f", NULL);
  // if (fork() == 0) {
  //   printf("Processes Tree");
  //   execl("/bin/ps", "ps", "-f", NULL);
  //   exit(0);
  // }

  for (int i = 0; i < 3; i++) {
    wait(NULL);
  }

  printf("All child processes are terminated");
  /*printf("Parent process id : %d\n", getpid());*/
  return 0;
}
