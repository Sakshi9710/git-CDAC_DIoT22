/*
    return values:
        0 --> Child Process Block
        -1 --> Child Process Creation Failed
        pid of the child or > 0 ---> parent block
        pid_t fork(void);
*/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
    pid_t ret;
    printf("--->Statement before fork --> \n");
    ret = fork();
    ret = fork();
    ret = fork();
     ret = fork();
    printf("--->Statement after fork --> \n");
}