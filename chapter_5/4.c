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

// fread和fwrite可以实现二进制IO，即标准IO不光可以IO字符类型

struct {
    int a;
    double d;
}item;

int main(int argc, char** argv)
{
    FILE* p = fopen("file1", "a+");
    double number[5] = {1,2,3,4,5};
    size_t result = 0;
    item.a = 0;
    item.d = 0;

    result = fwrite(number, sizeof(double), 5, p);
    printf("%ld\n", result);

    result = fwrite(&item, sizeof(item), 1, p);
    printf("%ld\n", result);

    fclose(p);
    p = fopen("file1", "r");

    double number1[5];

    result = fread(number1, sizeof(double), 5, p);
    printf("%ld\n", result);
    printf("%lf\n", number1[0]);
    printf("%lf\n", number1[1]);
    printf("%lf\n", number1[2]);
    printf("%lf\n", number1[3]);
    printf("%lf\n", number1[4]);

    return 0;
}
