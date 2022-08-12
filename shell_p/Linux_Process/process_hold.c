//Process on Hold 
//Process Execution

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
#include <stdlib.h>

int count = 10;
int main(int argc, char* argv[])
{
    pid_t ret;

    ret = fork();
    if (ret == 0 )
    {
        printf("Count Process block\n");
        count = count + 2;
        printf("Count value in child block  = %d\t",count);
    
    }
    else if (ret > 0 )
    {
        wait(NULL);
        printf("Parent Process block\n");
        count = count + 5;
        printf("Count value in Parent Block = %d\t",count);
        printf("ret value Parent = %d\t",ret);
    }
    else
    {
        printf("Child Process is not Created\n");
        exit(0);
    }
    printf("Final value is  = %d\t",count);

    return 0;
}

