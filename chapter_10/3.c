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

// pause挂起进程，直至该进程捕捉到了一个信号
// 只有执行了信号处理函数并返回后，pause才返回

void handler(){
    printf("signal catch\n");
}

int main(int argc, char** argv)
{
    signal(SIGCHLD, handler);
    pause();
    printf("can i get here?\n");

    return 0;
}
