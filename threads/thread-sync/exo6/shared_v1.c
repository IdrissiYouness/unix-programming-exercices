#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int x = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg) {
  while (1) {
    pthread_mutex_lock(&mutex);

    int old_x = x;
    x = 2 * x + 1;
    printf("Thread t1: %d -> %d\n", old_x, x);

    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main() {
  pthread_t t1;

  pthread_create(&t1, NULL, thread_function, NULL);

  while (1) {
    pthread_mutex_lock(&mutex);

    int old_x = x;
    x = x + 1;
    printf("Main thread: %d -> %d\n", old_x, x);

    pthread_mutex_unlock(&mutex);
  }

  pthread_join(t1, NULL);

  pthread_mutex_destroy(&mutex);

  return 0;
}
