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

// 命令行中创建FIFO
// mkfifo 1
// ls > 1
// 在另一个终端：cat < 1
// 顺序相反也可以，FIFO默认为阻塞

int main(int argc, char** argv)
{
    

    return 0;
}
