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

int main(int argc, char** argv)
{
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr = PTHREAD_MUTEX_INITIALIZER;
    int shared;
    pthread_mutexattr_getpshared(&attr, &shared);
    if(shared == PTHREAD_PROCESS_SHARED){
        printf("shared\n");
    }
    else{
        printf("private\n");
    }
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_PRIVATE);

    return 0;
}
