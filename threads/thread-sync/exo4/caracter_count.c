#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_t th1, th2;
void *count_a_1(void *arg);
void *count_a_2(void *arg);
char *str;
int main(int argc, char *argv[]) {
  void *returned_result;
  str = (char *)malloc(50 * sizeof(char));
  printf("Entrer la chaine de characteres : ");
  scanf("%s", str);

  pthread_create(&th1, NULL, count_a_1, NULL);
  pthread_create(&th2, NULL, count_a_2, NULL);
  pthread_join(th2, &returned_result);
  int result = (int)returned_result;
  printf("le nombre de charactere 'a' est: %d\n", result);
  return 0;
}

// fisrt thread count a in fisrt half and pass the result to the second thread
void *count_a_1(void *arg) {
  int count1 = 0;
  for (int i = 0; i < strlen(str) / 2; i++) {
    if (str[i] == 'a') {
      count1++;
    }
  }

  // printf("Count of 'a' in first half: %d\n", count1);
  pthread_exit((void *)count1);
}
// second thread count a in second half of the string and add the result to the
void *count_a_2(void *arg) {
  void *returned_result;
  pthread_join(th1, &returned_result);
  // char *str = (char *)arg;
  int count2 = 0;
  int count1 = (int)returned_result;
  for (int i = strlen(str) / 2; i < strlen(str); i++) {
    if (str[i] == 'a') {
      count2++;
    }
  }
  // printf("Count of 'a' in second half: %d\n", count2);
  pthread_exit((void *)(count1 + count2));
}
