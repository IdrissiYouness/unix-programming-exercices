#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 1024

int main(int argc, char *argv[]) {

  char buf[MAX];
  char reponse1[MAX], reponse2[MAX];

  mkfifo("fifo_s_to_c1", 0666);
  mkfifo("fifo_s_to_c2", 0666);
  mkfifo("fifo_c1_to_s", 0666);
  mkfifo("fifo_c2_to_s", 0666);

  mkfifo("fifo_s_ack_c1", 0666);
  mkfifo("fifo_s_ack_c2", 0666);

  printf("Entrez une chaine de caracteres : ");
  fgets(buf, MAX, stdin);

  // Envoi aux clients

  int fd1 = open("fifo_s_to_c1", O_WRONLY);
  if (fd1 == -1) {
    perror("open fifo_s_to_c1");
    exit(1);
  }
  write(fd1, buf, strlen(buf));
  close(fd1);

  int fd2 = open("fifo_s_to_c2", O_WRONLY);
  if (fd2 == -1) {
    perror("open fifo_s_to_c2");
    exit(1);
  }
  write(fd2, buf, strlen(buf));
  close(fd2);

  // Reception des reponses

  int fd3 = open("fifo_c1_to_s", O_RDONLY);
  if (fd3 == -1) {
    perror("open fifo_c1_to_s");
    exit(1);
  }
  read(fd3, reponse1, MAX);
  close(fd3);

  int fd4 = open("fifo_c2_to_s", O_RDONLY);
  if (fd4 == -1) {
    perror("open fifo_c2_to_s");
    exit(1);
  }
  read(fd4, reponse2, MAX);
  close(fd4);

  if (strcmp(reponse1, reponse2) == 0) {
    printf("Les deux clients ont renvoye la meme reponse : %s\n", reponse1);

    printf("Envoi de l'accusé de réception aux clients...\n");
    int fd5 = open("fifo_s_ack_c1", O_WRONLY);
    int fd6 = open("fifo_s_ack_c2", O_WRONLY);
    write(fd5, "OK", 3);
    write(fd6, "OK", 3);

    close(fd5);
    close(fd6);

  } else {
    printf("Les deux clients ont renvoyé des réponses différentes :\n");
    printf("Client 1 : %s\n", reponse1);
    printf("Client 2 : %s\n", reponse2);
  }

  unlink("fifo_s_to_c1");
  unlink("fifo_s_to_c2");
  unlink("fifo_c1_to_s");
  unlink("fifo_c2_to_s");
  unlink("fifo_s_ack_c1");
  unlink("fifo_s_ack_c2");
}
