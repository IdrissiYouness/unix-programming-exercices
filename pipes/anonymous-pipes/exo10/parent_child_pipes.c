#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * This program creates a pipe and forks three child processes.
 * The first two child processes write capital and small letters to the pipe,
 * while the third child process reads from the pipe and prints the output.
 * The program demonstrates inter-process communication using pipes.
 */

int main(int argc, char *argv[]) {
  pid_t pid1, pid2, pid3;
  int p[2]; // 0->read   1->write
  if (pipe(p) == -1) {
    perror("failed to open pipe");
    return 1;
  }
  pid1 = fork();
  if (pid1 == -1) {
    return 1;
  } else if (pid1 == 0) {
    close(p[0]);
    char buf[26];
    // dynamicaly fill buffer with capital letters
    for (int i = 0; i < 26; i++) {
      buf[i] = 'A' + i;
    }
    // for (int i = 0; i < 26; i++) {
    //   printf("%c ", buf[i]);
    // }
    for (int i = 0; i < 26; i += 3) {
      write(p[1], &buf[i], 3);
      sleep(1);
    }
    close(p[1]);
    exit(0);
  }

  pid2 = fork();
  if (pid2 == -1) {
    return 1;
  } else if (pid2 == 0) {
    close(p[0]);
    char buf[26];

    // fill dynamically buffer with small letters
    for (int i = 0; i < 26; i++) {
      buf[i] = 'a' + i;
    }

    for (int i = 0; i < 26; i += 3) {
      write(p[1], &buf[i], 3);
      sleep(1);
    }
    close(p[1]);
    exit(0);
  }

  pid3 = fork();
  if (pid3 == -1) {
    return 1;
  } else if (pid3 == 0) {
    close(p[1]);
    char buf[4];
    int n;
    while ((n = (read(p[0], buf, 4)) > 0)) {
      // buf[3] = '\0'; // null terminate the string
      printf("%s\n", buf);
      // when i ommit \n it is not printing and just blinking
      sleep(1);
    }
    close(p[0]);
    exit(0);
  }
  close(p[0]);
  close(p[1]);

  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);
  waitpid(pid3, NULL, 0);

  return EXIT_SUCCESS;
}
