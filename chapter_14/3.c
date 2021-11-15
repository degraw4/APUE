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
#include "tell_wait.h"

#define read_lock(fd, offset, whence, len)      lock_reg(fd, F_SETLK, F_RDLCK, (offset), (whence), (len))
#define readw_lock(fd, offset, whence, len)     lock_reg(fd, F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define write_lock(fd, offset, whence, len)     lock_reg(fd, F_SETLK, F_WRLCK, (offset), (whence), (len))
#define writew_lock(fd, offset, whence, len)    lock_reg(fd, F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define un_lock(fd, offset, whence, len)        lock_reg(fd, F_SETLK, F_UNLCK, (offset), (whence), (len))


int main(int argc, char** argv)
{
    

    return 0;
}
