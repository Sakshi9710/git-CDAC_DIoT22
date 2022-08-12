#include <stdio.h>
#include "addsub.h"

int main()
{
    int choice , num1 , num2;
    printf("Enter the operation to be performed :\n");
    printf("1)ADD\n");
    printf("2)SUB\n");
    scanf("%d",&choice);
    printf("Enter First Number\n");
    scanf("%d",&num1);
    printf("Enter Second Number\n");
    scanf("%d",&num2);

    if(choice == 1)
    {
        int out = addTwoNumbers(num1,num2);
        printf("%d + %d = %d \n",num1,num2,out);
    }
    else
    if(choice == 2)
    {
        int out = subTwoNumbers(num1,num2);
        printf("%d - %d = %d \n",num1,num2,out);
    }

    return 0;
}