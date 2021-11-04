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

int main(int argc, char** argv)
{
    int n;
    while((n = getc(stdin)) != EOF)
        if(putc(n, stdout) == EOF){
            printf("write error\n");
            exit(1);
        }
    if(ferror(stdin))
        printf("read error\n");
        exit(1);

    return 0;
}
