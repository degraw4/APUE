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

// readn和writen：自动处理每次read或者write不足的情况，遇到error则返回已经处理的字节数

ssize_t readn(int fd, void* buffer, size_t nbytes){
    size_t nleft = nbytes;
    ssize_t nread;
    while(nleft > 0){
        if((nread = read(fd, buffer, nleft)) < 0){   // error
            if(nleft == nbytes)
                return (-1);    // 一个没读到
            else   
                break;          // 读了一些
        }
        else if(nread == 0){
            break;              // EOF
        }
        nleft -= nread;
        buffer += nread;
    }
    return nbytes - nleft;
}

ssize_t writen(int fd, void* buffer, size_t nbytes){
    size_t nleft = nbytes;
    ssize_t nwrite;
    while(nleft > 0){
        if((nwrite = write(fd, buffer, nleft)) < 0){
            if(nleft == nbytes)
                return -1;
            else   
                break;
        }
        else if(nwrite == 0)
            break;
        nleft -= nwrite;
        buffer += nwrite;
    }
    return nbytes - nleft;
}