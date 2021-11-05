#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>

int main(int argc, char** argv)
{
    extern char** environ;
    printf("%s\n", environ[0]);
    printf("%s\n", environ[1]);

    return 0;
}
