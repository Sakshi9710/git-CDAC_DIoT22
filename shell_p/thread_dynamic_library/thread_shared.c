#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int shared_count = 0;
pthread_mutex_t mutex;

void* routine1()
{
    for (int i =0 ; i<100000000 ; i++)
    {
        pthread_mutex_lock(&mutex);
        shared_count++;
        pthread_mutex_unlock(&mutex);
    }   
}

int main(int argc, char* argv[])
{
    pthread_t t1;
    pthread_t t2;
    pthread_mutex_init(&mutex,NULL);
    // pthread_t t3;
    // pthread_t t4;

    if(pthread_create(&t1,NULL,routine1,NULL) != 0)
    {
        return 10;
    }
    
    if(pthread_create(&t2,NULL,routine1,NULL) != 0)
    {
        return 20;
    }
    
    // if(pthread_create(&t3,NULL,routine1,NULL) != 0)
    // {
    //     return 30;
    // }
   
    // if(pthread_create(&t4,NULL,routine1,NULL) != 0)
    // {
    //     return 50;
    // }
    
   pthread_mutex_destroy(&mutex);
   printf("number of times loop executed: %d \n",shared_count);

    return 0;
}