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

// fgets和fputs都原样IO，原样处理换行符
// fgets遇到换行符和null停止，返回null
// fputs遇到null停止，返回EOF

int main(int argc, char** argv)
{
    FILE* p = fopen("file", "r+");
    char buf[10];
    while(fgets(buf, 10, p) != NULL)
        printf("%s", buf);

    fputs("56", p);
    fputs("test\ntest", p);

    return 0;
}
