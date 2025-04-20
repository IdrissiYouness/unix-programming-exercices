// this exercise show how child process can ignore parent process signal

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void signal_handler(int signum) { printf("Child received SIGUSR1 signal\n"); }

int main() {
  pid_t pid;

  pid = fork();

  if (pid < 0) {
    perror("Fork failed");
    exit(1);
  } else if (pid == 0) {
    printf("Child process  PID: %d\n", getpid());

    signal(SIGUSR1, signal_handler);

    sigset_t block_mask;
    sigemptyset(&block_mask);
    sigaddset(&block_mask, SIGUSR1);

    printf("Child: Blocking SIGUSR1 for 30 seconds\n");
    sigprocmask(SIG_BLOCK, &block_mask, NULL);

    sleep(30);

    printf("Child: Unblocking SIGUSR1\n");
    sigprocmask(SIG_UNBLOCK, &block_mask, NULL);

    sleep(5);

    printf("Child process exiting\n");
    exit(0);
  } else {
    printf("Parent process started with PID: %d\n", getpid());
    printf("Child process has PID: %d\n", pid);

    sleep(2);

    printf("Parent: Sending SIGUSR1 to child (will be blocked)\n");
    kill(pid, SIGUSR1);

    sleep(32);
    printf("Parent: Sending SIGUSR1 to child again (should be received)\n");
    kill(pid, SIGUSR1);

    int status;
    waitpid(pid, &status, 0);

    printf("Parent: Child has exited\n");
    return 0;
  }
}
