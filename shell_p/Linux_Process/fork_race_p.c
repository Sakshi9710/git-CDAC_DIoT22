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
        
            printf("Child Count = %d\n",count);
            count = count + 2;
        
            printf("Final value in child block  = %d\t",count);
    
    }
    else if (ret > 0 )
    {
        
            printf("Parent Count = %d\n",count);
             count = count + 5;

            printf("Final value in Parent Block = %d\t",count);
    
    }
    else
    {
        printf("Child Process is not Created\n");
        exit(0);
    }
    printf("Final value is  = %d\t",count);

    return 0;
}

