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

// mmap和memcpy直接在内核缓冲区之间复制数据，而read和write则在用户缓冲区和内核缓冲区之间复制数据

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define threshold (1024*1024*1024)  // 1 GB

int main(int argc, char* argv[])
{
    int fdin, fdout;
    void *src, *dst;    // *跟在后面
    size_t left;
    off_t copied = 0;
    struct stat sbuf;

    if(argc != 3){
        printf("Argc error\n");
        exit(-1);
    }

    if((fdin = open(argv[1], O_RDONLY)) < 0){
        printf("%s open error\n", argv[1]);
        exit(-1);
    }

    if((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0){
        printf("%s open error\n", argv[2]);
        exit(-1);
    }

    if(fstat(fdin, &sbuf) < 0){
        printf("fstat error\n");
        exit(-1);
    }

    if(ftruncate(fdout, sbuf.st_size) < 0){
        printf("ftruncate error\n");
        perror("ftruncate");
        exit(-1);
    }

    while(copied < sbuf.st_size){
        if((sbuf.st_size - copied) > threshold)
            left = threshold;
        else
            left = sbuf.st_size - copied;
        if((src = mmap(0, left, PROT_READ, MAP_SHARED, fdin, copied)) == MAP_FAILED){
            printf("fdin mmap error\n");
            exit(-1);
        }
        if((dst = mmap(0, left, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, copied)) == MAP_FAILED){
            printf("fdout mmap error\n");
            exit(-1);
        }
        memcpy(dst, src, left);
        msync(dst, left, MS_SYNC);
        munmap(src, left);
        munmap(dst, left);
        copied += left;
    }

    return 0;
}
