#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *read(void *arg);
void *write(void *arg);
pthread_t thread1, thread2;

int main(int argc, char *argv[]) {
  pthread_create(&thread1, NULL, read, NULL);
  pthread_create(&thread2, NULL, write, NULL);
  pthread_join(thread2, NULL);
}

void *read(void *arg) {
  char *c = (char *)malloc(50 * sizeof(char));
  printf("Enter the caracters: ");
  scanf("%s", c);
  pthread_exit((void *)c);
}

void *write(void *arg) {
  void *c;
  pthread_join(thread1, &c);
  printf("%s\n", (char *)c);
  return NULL;
}
