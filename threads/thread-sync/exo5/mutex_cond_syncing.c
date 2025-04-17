#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* here we access the global buffer of caracteres using mutex and condition
 * variable */

#define MAXSIZE 10

pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_cond = PTHREAD_COND_INITIALIZER;

char buffer[MAXSIZE];
int fillPos = 0;
int thread_turn = 0; // 0 for thread 1 fillwithA, 1 for thread 2 filllwithB

void *fillWithA(void *arg);
void *fillWithB(void *arg);

int main(int argc, char *argv[]) {
  pthread_t th1, th2;
  pthread_create(&th1, NULL, fillWithA, NULL);
  pthread_create(&th2, NULL, fillWithB, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  printf("The final Buffer values are: \n");
  for (int i = 0; i < MAXSIZE; i++) {
    printf("%c ", buffer[i]);
  }
  printf("\n");
}

void *fillWithA(void *arg) {
  pthread_mutex_lock(&buffer_mutex);
  while (fillPos < MAXSIZE) {
    while (thread_turn != 0) {
      pthread_cond_wait(&buffer_cond, &buffer_mutex);
    }
    buffer[fillPos] = 'a';
    fillPos++;
    thread_turn = 1;
    pthread_cond_signal(&buffer_cond);
  }
  pthread_mutex_unlock(&buffer_mutex);
  pthread_exit(NULL);
}

void *fillWithB(void *arg) {
  while (fillPos < MAXSIZE) {
    while (thread_turn != 1) {
      pthread_cond_wait(&buffer_cond, &buffer_mutex);
    }
    buffer[fillPos] = 'b';
    fillPos++;
    thread_turn = 0;
    pthread_cond_signal(&buffer_cond);
  }
  pthread_mutex_unlock(&buffer_mutex);
  pthread_exit(NULL);
}
