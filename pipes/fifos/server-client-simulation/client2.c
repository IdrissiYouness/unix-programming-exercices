#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 1024

int compare(const void *a, const void *b) { return (*(char *)b - *(char *)a); }

int main() {
  int fd1, fd2, fd3;
  char buf[MAX], server_ack[MAX];

  fd1 = open("fifo_s_to_c2", O_RDONLY);
  read(fd1, buf, sizeof(buf));
  close(fd1);

  int len = strlen(buf);
  qsort(buf, len, sizeof(char), compare);
  printf("Client 2 - Chaine triee en ordre decroissant: %s\n", buf);

  fd2 = open("fifo_c2_to_s", O_WRONLY);
  write(fd2, "Done", 5);
  close(fd2);

  fd3 = open("tube_s_ack_c2", O_RDONLY);
  read(fd3, server_ack, sizeof(server_ack));
  printf("Client 2 a reçu du serveur: %s\n", server_ack);
  close(fd3);

  return 0;
}
