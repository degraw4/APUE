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
#include <setjmp.h>

// 存在CPU和寄存器中的变量恢复为setjmp时的值
// 存在存储器中的变量恢复为longjmp时的值
// 寄存器由于在栈帧中，会回滚；存储器已经保存，不会回滚
// 全局、静态和volatile变量不受优化的影响，都存在存储器中
// 优化可能导致自动变量和寄存器变量存在寄存器中

static jmp_buf buf;
static int globval;

static void func2(){
    longjmp(buf, 1);
}

static void func1(int i, int j, int k, int l){
    printf("in func1:\n");
    printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n", globval ,i, j, k, l);
    func2();
}

int main(int argc, char** argv)
{
    int autoval = 1;
    register int regival = 2;
    volatile int volaval = 3;
    static int statval = 4;
    globval = 5;

    if(setjmp(buf) != 0){
        printf("after jmp:\n");
        printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n", globval ,autoval, regival, volaval, statval);
        return 0;
    }

    autoval = 91;
    regival = 92;
    volaval = 93;
    statval = 94;
    globval = 95;

    func1(autoval, regival, volaval, statval);

    return 0;
}
