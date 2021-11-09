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

// pending和mask的区别

sigset_t new_mask, old_mask, pending_mask;

int main(int argc, char** argv)
{
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);
    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);
    sigpending(&pending_mask);

    // 验证mask后不产生SIGINT, SIGINT是否pending, the answer is no
    if(sigismember(&pending_mask, SIGINT)){
        printf("SIGINT is in pending\n");
    }
    else{
        printf("SIGINT is not in pending\n");
    }
    sigprocmask(SIG_SETMASK, &old_mask, NULL);

    return 0;
}
