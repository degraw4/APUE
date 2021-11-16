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

// fopen: pipe + fork + exec

int main(int argc, char** argv)
{
    FILE* fp = popen("ls -ah", "r");
    char buffer[1024] = "";
    fread(buffer, 1, 1024, fp);
    printf("%s", buffer);
    fclose(fp);

    return 0;
}
