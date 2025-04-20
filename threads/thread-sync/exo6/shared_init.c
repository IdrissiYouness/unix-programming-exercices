#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int x = 0;

void *thread_function(void *arg) {
  while (1) {
    x = 2 * x + 1;
    printf("Thread t1: x = %d\n", x);
  }
  return NULL;
}

int main() {
  pthread_t t1;
  pthread_create(&t1, NULL, thread_function, NULL);

  while (1) {
    x = x + 1;
    printf("Main thread: x = %d\n", x);
  }

  pthread_join(t1, NULL);
  return 0;
}
