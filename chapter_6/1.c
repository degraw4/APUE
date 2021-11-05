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
#include <time.h>

int main(int argc, char** argv)
{
    time_t t = time(NULL);
    printf("%ld\n", t);

    struct tm* t1 = localtime(NULL);

    t = mktime(t1);

    return 0;
}
