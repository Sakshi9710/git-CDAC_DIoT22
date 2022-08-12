#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int count = 0;

void* routine1()
{
    for (int i =0 ; i<100000000 ; i++)
    {
        count++;
    }   
}

int main(int argc, char* argv[])
{
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    pthread_t t4;

    if(pthread_create(&t1,NULL,routine1,NULL) != 0)
    {
        return 10;
    }
    
    if(pthread_create(&t2,NULL,routine1,NULL) != 0)
    {
        return 20;
    }
    
    if(pthread_create(&t3,NULL,routine1,NULL) != 0)
    {
        return 30;
    }
   
    if(pthread_create(&t4,NULL,routine1,NULL) != 0)
    {
        return 50;
    }
    // pthread_join(t1,NULL);
    // pthread_join(t2,NULL);
    // pthread_join(t3,NULL);
    // pthread_join(t4,NULL);
   printf("number of times loop executed: %d \n",count);

    return 0;
}