#include<pthread.h>
#include<stdio.h>
#include "routine1.h"
#include "routine2.h"
#include "sum.h"
#include "sub.h"

int main(int argc, char* argv[])
{
    int num1 ,num2;
    
    printf("Enter First Number\n");
    scanf("%d",&num1);
    printf("Enter Second Number\n");
    scanf("%d",&num2);

    int res1 = sum(num1 , num2);
    int res2 = sub(num1 , num2);

    pthread_t t1;
    pthread_t t2;

    //Create a Thread
    pthread_create(&t1,NULL,&routine1(res1 , res2),NULL);
    pthread_create(&t2,NULL,&routine2(res1 , res2),NULL);
    pthread_join(t2,NULL);
    pthread_join(t1,NULL);

    return 0;
}