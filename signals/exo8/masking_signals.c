// This program demonstrates how to block and unblock signals
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int signum) { printf("\nReceived SIGINT (Ctrl+C)\n"); }

void sigquit_handler(int signum) { printf("\nReceived SIGQUIT (Ctrl+\\)\n"); }

int main() {
  signal(SIGINT, sigint_handler);
  signal(SIGQUIT, sigquit_handler);

  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGQUIT);

  printf("Program started. Try pressing Ctrl+C or Ctrl+\\ during execution.\n");

  printf("Blocking SIGINT and SIGQUIT for 20 seconds...\n");
  sigprocmask(SIG_BLOCK, &mask, NULL);

  for (int i = 0; i < 20; i++) {
    printf("Signals blocked for %d more seconds\n", 20 - i);
    sleep(1);
  }

  printf("Unblocking SIGINT and SIGQUIT\n");
  sigprocmask(SIG_UNBLOCK, &mask, NULL);

  printf("Signals are now unblocked. Try pressing Ctrl+C or Ctrl+\\ now.\n");
  printf("Program will exit in 10 seconds...\n");

  sleep(10);

  printf("Program exiting normally.\n");
  return 0;
}
