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

// 当把输出定向到文件时，其为全缓冲，遇到\n不会像终端设备一样主动flush
// 因此fork后，由于没有flush，"beforn fork\n"仍在缓冲区中，被子进程复制了过去，导致输出了两次

int main(int argc, char** argv)
{
    int i = 0;
    FILE* p = fopen("file", "r+");
    fprintf(p, "beforn fork\n"); // dont flush stdout
    //fflush(p);
    if(fork() == 0){
        i = 1;
    }
    fprintf(p, "i = %d\n", i);
    exit(0);

    return 0;
}
