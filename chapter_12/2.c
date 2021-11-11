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

// sigwait：
    // 监听被阻塞的信号，如果所监听的信号产生了，则将其从进程的pending队列中移出来
    // sigwait并不改变信号的mask
    // 如果要确保线程sigwait收到该信号，所有线程必须block这个信号，因为如果自己不block就没有未决状态(阻塞状态)信号，别的线程不block就有可能当信号过来时被其他的线程处理掉
    
// 在一个线程中调用signal或者sigaction，会改变所有线程中的信号处理函数，而不是仅仅是该线程的信号处理函数

int main(int argc, char** argv)
{
    

    return 0;
}
