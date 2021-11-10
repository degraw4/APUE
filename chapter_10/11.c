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

// sleep被挂起，直到时间结束或者捕捉到信号并从信号处理程序返回
// 第二种情况，sleep返回的是捕捉到信号时的剩余时间，尽管信号处理程序的时间可能长于剩余时间

void handler(){
    sleep(5);
}

int main(int argc, char** argv)
{
    signal(SIGINT, handler);
    int ret = sleep(3);
    printf("%d\n", ret);

    return 0;
}
