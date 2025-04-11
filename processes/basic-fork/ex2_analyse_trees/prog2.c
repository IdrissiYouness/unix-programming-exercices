#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void doit(){
  fork();
  fork();
  printf("Hello!\n");
  
}

int main(int argc, char *argv[])
{
  doit();
  printf("Hello!\n");
  exit(0);
}
