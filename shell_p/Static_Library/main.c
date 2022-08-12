#include<stdio.h>
#include "basic-header.h"

int main()
{
    int num1 ,num2;
    int choice, res;
    printf("Enter First Number\n");
    scanf("%d",&num1);
    printf("Enter Second Number\n");
    scanf("%d",&num2);
    printf("Enter your Choice:\n");
    printf("[1]=> ADDITION\n");
    printf("[2]=> SUBTRACTION\n");
    printf("[3]=> MULTIPLY\n");
    printf("[4]=> DIVISION\n");
    scanf("%d",&choice);
    
    switch(choice)
    {
        case 1 : res = add(num1 , num2);
            printf("addition of %d + %d = %d\n",num1,num2,res);
            break;
        case 2 : res = sub(num1 , num2);
            printf("subtraction of %d - %d = %d\n",num1,num2,res);
            break;
        case 3 : res = mul(num1 , num2);
            printf("multiplication of %d * %d = %d\n",num1,num2,res);
            break;
        case 4 : res = div(num1 , num2);
            printf("division of %d / %d = %d\n",num1,num2,res);
            break;
        default :
            break;
    }

    return 0;
}