#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t th1, th2;

void *lire(void *arg) {
  int *number = malloc(sizeof(int));
  printf("Entrez un entier : ");
  scanf("%d", number);
  pthread_exit((void *)number);
}

void *calculeracine(void *arg) {
  void *m;
  pthread_join(th1, &m);
  int *number = (int *)m;
  double *r = malloc(sizeof(double));
  *r = sqrt((double)(*number));
  pthread_exit((void *)r);
}

int main() {
  void *m;
  pthread_create(&th1, NULL, lire, NULL);
  pthread_create(&th2, NULL, calculeracine, NULL);
  pthread_join(th2, &m);
  double *r = (double *)m;
  printf("Le resultat est : %lf\n", *r);
  return 0;
}
