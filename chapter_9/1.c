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

// setsid建立新会话

int main(int argc, char** argv)
{
    pid_t ret = setsid();
    printf("%d\n", ret);

    if(fork() == 0){
        ret = setsid();
        printf("%d\n", ret);
    }
    else{
        exit(0);
    }

    return 0;
}
