/*
    library-function --> pthread_create -> man 3 pthread_create
*/

#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
//Thread rpoutine -->
void *routine1(void *msg)
{
    printf("I am from routine 1 \n");
    sleep(10);
    printf("This is thread1 Program\n");
    sleep(40);
    printf("1 we are studing Kernel Os\n");
}

void *routine2(void *msg)
{
    printf("I am from routine 2 \n");
    sleep(10);
    printf("This is thread2 Program\n");
    
    printf("2 we are studing Kernel Os\n");
}

void *message(void *msg)
{
    printf("This is Embedded Linux Module \n");
    sleep(10);
    printf("Kernel OS is a part of this Module \n");

}

int main(int argc, char* argv[])
{
    pthread_t t1;
    pthread_t t2;
    pthread_t topic;
    //Create a Thread
    pthread_create(&t1,NULL,routine1,NULL);
    pthread_create(&t2,NULL,routine2,NULL);
    pthread_create(&topic,NULL,message,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(topic,NULL);
}