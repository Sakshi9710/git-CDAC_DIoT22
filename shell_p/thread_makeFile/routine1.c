#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
void *routine1(int res1, int res2)
{
    printf("I am from routine 1 \n ");
    //sleep(2);
    printf("Sum of Two Number is = %d\n",res1);
    //sleep(5);
    printf("Sub of Two Number is = %d\n",res2);
}