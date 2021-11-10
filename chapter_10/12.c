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

// sigaction

void handler(){
    printf("\ncatch\n");
}

int main(int argc, char** argv)
{
    struct sigaction new_action, old_action;
    sigset_t old_mask;
    new_action.sa_handler = handler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;
    sigaction(SIGINT, &new_action, &old_action);

    sleep(5);

    return 0;
}
