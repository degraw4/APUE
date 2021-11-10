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
#include <setjmp.h>

// 只要在信号处理程序中调用了siglongjmp，都要使用flag判断是否可以运行处理函数，并且运行完毕要恢复flag

static sigjmp_buf buffer;
static int flag = 0;

void handler(){
    if(!flag)
        return; // not ready for siglongjmp...
    printf("catch\n");
    flag = 0;   // 重新设置flag，防止siglongjmp后再次捕捉该信号导致再次进入此函数
    siglongjmp(buffer, 1);
}

int main(int argc, char** argv)
{
    signal(SIGINT, handler);
    if(sigsetjmp(buffer, 1) != 0){
        printf("jump over\n");
        return 0;
    }
    flag = 1;   // sigsetjmp设置完毕，可以跳转
    pause();

    return 0;
}
