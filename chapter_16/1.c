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
    // socket地址数据结构
    struct sockaddr a;
    struct sockaddr_in b;
    struct sockaddr_in6 c;
    
    // IP地址的二进制和文本的转换
    char buf[130] = "";
    void* addr = malloc(128);
    inet_pton(AF_INET, "192.168.23.43", addr);
    inet_ntop(AF_INET, addr, buf, 130);
    printf("addr is %s\n", buf);

    return 0;
}
