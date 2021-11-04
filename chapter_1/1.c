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

// ./a.out <file1 >file2

#define BUFFERSIZE 4096

int main(int argc, char** argv)
{
    int n;
    char buffer[BUFFERSIZE];
    while((n = read(STDIN_FILENO, buffer, BUFFERSIZE)) > 0)
        if(write(STDOUT_FILENO, buffer, n) != n){
            printf("write error\n");
            exit(1);
        }
    if(n < 0)
        printf("read error\n");
        exit(1);

    return 0;
}
