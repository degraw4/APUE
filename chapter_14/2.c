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

// 记录锁
// 记录锁与文件和进程相关
    // 进程终止，该进程的锁全部释放
    // 文件描述符关闭，该进程在改文件描述符上的锁全部释放(但改描述符指向的文件由其他进程设置的锁不会释放)
        // 即在一个进程内，记录锁是和文件相关的，不论该文件open或者dup产生了几个描述符

#define read_lock(fd, offset, whence, len)      lock_reg(fd, F_SETLK, F_RDLCK, (offset), (whence), (len))
#define readw_lock(fd, offset, whence, len)     lock_reg(fd, F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define write_lock(fd, offset, whence, len)     lock_reg(fd, F_SETLK, F_WRLCK, (offset), (whence), (len))
#define writew_lock(fd, offset, whence, len)    lock_reg(fd, F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define un_lock(fd, offset, whence, len)        lock_reg(fd, F_SETLK, F_UNLCK, (offset), (whence), (len))

pid_t lock_test(int fd, int lock_type, off_t offest, int whence, int len){
    struct flock lock;
    
    lock.l_type = lock_type;
    lock.l_start = offest;
    lock.l_whence = whence;
    lock.l_len = len;

    fcntl(fd, F_GETLK, &lock);
    if(lock.l_type == F_UNLCK)
        return (0);
    return (lock.l_pid);
}

int main(int argc, char** argv)
{
    

    return 0;
}
