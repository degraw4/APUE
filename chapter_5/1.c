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

// 多个进程追加写同一个文件，都可以正确的写入

int main(int argc, char** argv)
{
    if(fork() == 0){
        FILE* p = fopen("file", "a+");
        fputs("123\n", p);
    }
    else{
        FILE* p = fopen("file", "a+");
        fputs("abc\n", p);
    }

    return 0;
}
