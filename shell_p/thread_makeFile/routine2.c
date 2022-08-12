#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
void *routine2(int res1, int res2)
{
    printf("I am from routine 2 \n ");
    //sleep(5);
    printf("Sum of Two Number is = %d\n",res1);
    //sleep(10);
    printf("Sub of Two Number is = %d\n",res2);
}