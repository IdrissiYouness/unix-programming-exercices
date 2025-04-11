#include <pthread.h>
#include <stdio.h>

void *fun(void *arg);
int main() {
  int n;
  printf("Enter the number of threads you want:");
  scanf("%d", &n);
  pthread_t threads[n];
  for (int i = 0; i < n; i++) {
    pthread_create(&threads[i], NULL, fun, NULL);
    pthread_join(threads[i], NULL);
  }
  /*for (int i=0; i<n; i++ ) {*/
  /*    pthread_join(threads[i],NULL);*/
  /*}*/

  return 0;
}

void *fun(void *arg) {
  printf("Hello World\n");
  pthread_exit(NULL);
}
