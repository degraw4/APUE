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

// 登记终止处理函数，一个进程最多登记32个

void exit_func1(){
    printf("this is first exit handler\n");
}

void exit_func2(){
    printf("this is second exit handler\n");
}

int main(int argc, char** argv)
{
    atexit(exit_func1);
    atexit(exit_func2);
    atexit(exit_func1);
    fork();

    return 0;
}
