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

// fgetc, fputc中，int和char可以相互转换

int main(int argc, char** argv)
{
    FILE* p = fopen("file", "r+");
    int c;
    while((c = fgetc(p)) != EOF){
        printf("%c", c);
    }

    fputc('4', p);

    return 0;
}
