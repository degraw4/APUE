#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#include <stddef.h>

#define QLEN 10

int server_listen(const char* name){
    int fd, len, err, rval;
    struct sockaddr_un un;
    if(strlen(name) >= sizeof(un.sun_path)){
        printf("name is too long\n");
        return -1;
    }
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    unlink(name);
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, name);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(name);
    bind(fd, &un, sizeof(len));
    listen(fd, QLEN);
    return fd;
}

int main(int argc, char* argv[])
{
    

    return 0;
}
