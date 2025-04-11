#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
  if (fork()==0){
      if (fork()) {
        printf("Hello!\n");
      }
  }
}
