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

void handler(int signal){
    if(signal == SIGPIPE)
        printf("catch SIGPIPE\n");
}

int main(int argc, char** argv)
{
    int fd_1[2], fd_2[2];
    char buffer[1024] = "";
    pipe(fd_1);
    pipe(fd_2);
    signal(SIGPIPE, handler);

    // test read while pipe close
    {
        close(fd_1[1]);
        int n = read(fd_1[0], buffer, 1024);
        printf("n is %d\n", n);
    }
    // test write while pipe clode
    {
        close(fd_2[0]);
        int n = write(fd_2[1], "test", 4);
        printf("n is %d\n", n);
    }

    return 0;
}
