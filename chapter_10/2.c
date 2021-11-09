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

// signal handler也可以是无参数的函数
// 如何使用 handler + alarm 循环定时

void handler(){
    printf("hello\n");
    alarm(1);
}

int main(int argc, char** argv)
{
    signal(SIGALRM, handler);
    handler();
    for(int i = 0; ; ++i){
        printf("sleep %d\n", i);
        sleep(1);
    }

    return 0;
}
