#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h> 

int main(int argc, char* argv[])
{
    int sockfd, val = 1;
    // SO_REUSEADDR使得可以重用band中的地址
    setsockopt(sockfd, IPPROTO_TCP, SO_REUSEADDR, &val, sizeof(int));
    
    // 设置sockfd的所有权
    fcntl(sockfd, F_SETOWN, getpid());

    return 0;
}
