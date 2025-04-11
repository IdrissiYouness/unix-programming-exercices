#include <math.h>
#include <pthread.h>
#include <stdio.h>

double r;
int d;
pthread_t th1, th2;

void *lire(void *arg);
void *calcule_racine(void *arg);

int main(int argc, char *argv[]) {
  pthread_create(&th1, NULL, lire, NULL);
  pthread_create(&th2, NULL, calcule_racine, NULL);

  pthread_join(th2, NULL);

  return 0;
}

void *lire(void *arg) {
  printf("Entrez un nombre : ");
  scanf("%d", &d);
  return NULL;
}

void *calcule_racine(void *arg) {
  // Attendre que le thread de lecture ait terminé
  pthread_join(th1, NULL);
  r = sqrt((double)d);
  printf("La racine carrée de %d est : %f\n", d, r);
  return NULL;
}
