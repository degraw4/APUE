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
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h> 

// connect
// getsockname
// getperrname

int connect_retry(int sockfd, const struct sockaddr *addr, socklen_t len){
    int MAXSLEEP = 128;
    for(int second = 1; second <= MAXSLEEP; second <<= 1){
        if(connect(sockfd, addr, len) == 0){
            // connect success
            return 0;
        }
        // delay before trying
        if(second <= MAXSLEEP)
            sleep(second);
    }
    // can't connect after tried many times
    return -1;
}

int main(int argc, char* argv[])
{
    struct sockaddr_in ser;
    bzero(&ser, sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_port = htons(atoi("9080")); 
    inet_pton(AF_INET, "192.168.1.26", &ser.sin_addr);

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&ser, sizeof(struct sockaddr));

    struct sockaddr addr;
    int len = sizeof(struct sockaddr);
    getsockname(socketfd, &addr, &len);
    char buf[130] = "";
    inet_ntop(AF_INET, addr.sa_data, buf, 130);
    printf("addr is %s\n", buf);

    getpeername(socketfd, &addr, &len);

    return 0;
}
