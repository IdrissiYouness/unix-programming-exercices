#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int x = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int child_thread_done = 0;
int child_thread_first = 1;

void *thread_function(void *arg) {
  while (1) {
    pthread_mutex_lock(&mutex);

    int old_x = x;
    x = 2 * x + 1;
    printf("Thread t1: %d -> %d\n", old_x, x);

    child_thread_done = 1;
    child_thread_first = 0;
    pthread_cond_signal(&cond);

    while (child_thread_done && !child_thread_first) {
      pthread_cond_wait(&cond, &mutex);
    }

    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main() {
  pthread_t t1;
  pthread_create(&t1, NULL, thread_function, NULL);
  pthread_mutex_lock(&mutex);
  while (!child_thread_done && child_thread_first) {
    pthread_cond_wait(&cond, &mutex);
  }
  pthread_mutex_unlock(&mutex);

  while (1) {
    pthread_mutex_lock(&mutex);

    int old_x = x;
    x = x + 1;
    printf("Main thread: %d -> %d\n", old_x, x);

    child_thread_done = 0;

    pthread_cond_signal(&cond);

    while (!child_thread_done && !child_thread_first) {
      pthread_cond_wait(&cond, &mutex);
    }

    pthread_mutex_unlock(&mutex);
  }

  pthread_join(t1, NULL);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);

  return 0;
}
