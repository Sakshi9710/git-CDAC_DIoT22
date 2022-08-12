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

int sum(int , int );
int sub(int , int );
int number1 , number2; 
int main(int argc, char* argv[])
{
    pid_t ret;
    printf("Enter Number 1 : \n");
    scanf("%d",&number1);
    printf("Enter Number 2 : \n");
     scanf("%d",&number2);
    ret = fork();
    if (ret == 0 )
    {
        //child Process Block
        printf("cpid = %d\n",getpid());
        printf("cppid = %d\n",getppid());
        int result = sum(number1 , number2);
        printf("Sum is : %d + %d = %d\n",number1 , number2, result);
    }
    else if (ret > 0 )
    {
        //parent Process Block
        printf("ppid = %d\n",getpid());
        printf("pppid = %d\n",getppid());
        int result = sub(number1 , number2);
        printf("Sub is : %d - %d = %d\n",number1 , number2, result);
    }
    else
    {
        printf("Failed to create a child process\n");
        exit(0);
    }
    printf("fork ret value = %d\t",ret);
    printf("Hello From MultiProcessing\n");
    sleep(70);
    return 0;
}

int sum(int num1, int num2 )
{
    int result = num1 + num2;
    return result;
}

int sub(int num1, int num2 )
{
    int result = num1 - num2;
    return result;
}