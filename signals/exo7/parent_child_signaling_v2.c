#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void signal_handler() {
  sleep(30);
  printf("Child receive the signal after 30s");

  signal(SIGUSR1, SIG_DFL); // reinstall the default behavior after tweaking
  // the SIGUSR1 work //u should uncomment it
}

int main() {
  pid_t pid;
  pid = fork();

  if (pid < 0) {
    perror("fork fail");
    exit(1);
  } else if (pid == 0) {
    signal(SIGUSR1, signal_handler);
    pause(); // wait till signal reveived
    // now received the signal i can received
    exit(0);
  } else {
    sleep(1); // let the child have chance to install the handler and prepare
    kill(pid, SIGUSR1); // send the signal
    wait(NULL);         // wait the child terminate and get his status code
  }
}
