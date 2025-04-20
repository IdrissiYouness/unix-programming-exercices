#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char global_array[10];

void *thread1_function(void *arg) {
  for (int i = 0; i < 10; i += 2) {
    global_array[i] = 'a';
    printf("Thread 1 wrote 'a' at index %d\n", i);
  }
  return NULL;
}

void *thread2_function(void *arg) {
  for (int i = 1; i < 10; i += 2) {
    global_array[i] = 'b';
    printf("Thread 2 wrote 'b' at index %d\n", i);
  }
  return NULL;
}

int main() {
  pthread_t thr1, thr2;

  pthread_create(&thr1, NULL, thread1_function, NULL);
  pthread_create(&thr2, NULL, thread2_function, NULL);

  pthread_join(thr2, NULL);
  pthread_join(thr1, NULL);

  printf("Array content: ");
  for (int i = 0; i < 10; i++) {
    printf("%c ", global_array[i]);
  }
  printf("\n");

  return 0;
}
