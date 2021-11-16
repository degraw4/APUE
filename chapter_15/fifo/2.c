#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char** argv)
{
    if(fork() > 0){
        // 默认阻塞方式打开
        int fd = open("1", O_RDONLY);
        printf("parent open fifo\n");
    }
    else{
        sleep(1);
        int fd = open("1", O_RDWR);
    }


    return 0;
}
