#include<stdio.h>
#include "sum.h"
#include "mul.h"
#include "sub.h"
#include "div.h"

int main()
{
    int num1 ,num2;
    printf("Leerning How to make FileEnter First Time\n");
    printf("Enter First Number\n");
    scanf("%d",&num1);
    printf("Enter Second Number\n");
    scanf("%d",&num2);
    int res1 = sum(num1 , num2);
    int res2 = mul(num1 , num2);
    int res3 = sub(num1 , num2);
    int res4 = div(num1 , num2);

    printf("%d + %d = %d\n",num1,num2,res1);
    printf("%d * %d = %d\n",num1,num2,res2);
    printf("%d - %d = %d\n",num1,num2,res3);
    printf("%d / %d = %d\n",num1,num2,res4);

    return 0;
}