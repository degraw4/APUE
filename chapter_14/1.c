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

// 将文件描述符变为非阻塞

int main(int argc, char** argv)
{
    // 对于正在open的fd，设置O_NONBLOCK
    int fd = open("./file", O_RDWR | O_NONBLOCK);
    
    // 对于已经打开的fd，用fcntl设置文件属性
        // 文件属性/FL：O_RDWR，O_APPEND，O_NONBLOCK
        // 文件描述符属性/FD：FD_CLOEXEC
    int val  =fcntl(fd, F_GETFL, 0);
    val |= O_NONBLOCK;
    fcntl(fd, F_SETFL, val);

    return 0;
}
