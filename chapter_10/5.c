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

// 防止read超时，使用alarm及其信号处理函数
// 避免alarm计时结束和read开始的竞争，使用longjmp
// read后面的alarm(0)是为了read及时结束后清空alarm

static jmp_buf buffer;
char buf[1024];

void handler(){
    longjmp(buffer, 1);
}

int main(int argc, char** argv)
{
    signal(SIGALRM, handler);
    if(setjmp(buffer) != 0){
        printf("read timed out\n");
        return 1;
    }
    alarm(10);
    read(STDIN_FILENO, buf, 1024);
    alarm(0);
    write(STDOUT_FILENO, buf, 1024);

    return 0;
}
