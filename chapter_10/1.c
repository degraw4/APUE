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

// 非root发送kill，接收者的 实际用户ID or 有效用户ID 要等于发送者的 实际用户ID or 有效用户ID
// alarm返回值：0或以前alarm剩余秒数

int main(int argc, char** argv)
{
    int ret = kill(1, SIGCHLD);
    printf("%d\n", ret);
    ret = kill(-1, SIGCHLD);
    printf("%d\n", ret);
    ret = alarm(10);
    printf("%d\n", ret);
    sleep(1);
    ret = alarm(10);
    printf("%d\n", ret);

    return 0;
}
