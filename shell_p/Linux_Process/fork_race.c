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

long int final_value;
int main(int argc, char* argv[])
{
    pid_t ret;
    int count1 ,count2 ;
    ret = fork();
    if (ret == 0 )
    {
        for(count1 = 0;count1<=100 ; count1++)
        {
            printf("Parent Count = %d\n",count1);
            final_value = final_value - 1;
            printf("Final value  via parent  = %ld\t",final_value);
        }
    }
    else if (ret > 0 )
    {
        for(count2 = 0;count2<=100 ; count2++)
        {
            printf("Child Count = %d\n",count2);
            final_value = final_value +1;
            printf("Final value via child  = %ld\t",final_value);
        }
    }
    else
    {
        printf("Child Process is not Created\n");
        exit(0);
    }
    printf("Final value is  = %ld\t",final_value);

    return 0;
}

