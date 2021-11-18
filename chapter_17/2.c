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

// 创建UNIX域套接字地址，并将其和fd绑定

int main(int argc, char* argv[])
{
    int fd, size;
    struct sockaddr_un un;
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, "unix_socket_test");
    //strcpy(un.sun_path, "/home/soar/apue/unix_socket_test");
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
    if(bind(fd, (struct sockaddr*)&un, size) < 0){
        perror("bind failed");
        exit(-1);
    }
    printf("UNIX addr bind\n");
    return 0;
}
