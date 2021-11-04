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

// stat也可以打开目录文件

int main(int argc, char** argv)
{
    struct stat s;
    stat("test", &s);
    printf("size %ld\n", s.st_size);
    printf("inode %ld\n", s.st_ino);
    printf("%d\n", S_ISDIR(s.st_mode));
    printf("%d\n", S_ISREG(s.st_mode));

    return 0;
}
