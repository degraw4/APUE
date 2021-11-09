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

// 使用pause实现sleep
// 为了避免alarm的返回和pause形成竞争导致pause永久阻塞，使用longjmp避免返回后遇到pause
// 但是SIGALRM可能中断了其他信号处理程序，longjmp直接返回导致该程序未运行结束

static jmp_buf buffer;

void handler(){
    longjmp(buffer, 1);
}

int Sleep(int second){
    signal(SIGALRM, handler);
    if(setjmp(buffer) == 0){
        alarm(second);
        pause();
    }
    return alarm(0);
}

int main(int argc, char** argv)
{
    Sleep(5);

    return 0;
}
