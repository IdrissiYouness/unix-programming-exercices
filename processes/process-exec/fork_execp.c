#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid = fork();

  if (pid < 0) {
    perror("fork");
    return 1;
  }

  if (pid == 0) {
    execlp("ls", "ls", "-l", NULL);
    // execlp("ls", "ls", "-a", NULL);
    perror("execlp failed");
    return 2;
  } else {
    int status;
    wait(&status);
    // printf("Child process finished with status: %d\n", status);
    if (WIFEXITED(status)) {
      printf("Child process exited with status: %d\n", WEXITSTATUS(status));
    } else {
      printf("Child process exited abnormally\n");
    }
  }

  return 0;
}
