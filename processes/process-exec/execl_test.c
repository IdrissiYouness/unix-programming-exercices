#include <unistd.h>

int main()
{
    fork();
    execl("/bin/ls", "ls", "-l", NULL);
    fork();
}
