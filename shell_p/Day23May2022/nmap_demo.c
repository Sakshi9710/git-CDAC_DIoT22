#include<stdio.h>
#include<stdint.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<wait.h>
#include<stdlib.h>

#define PAGESIZE 4096
int v = 5;
 int main(int argc , char *argv)
 {
     uint8_t *shared_memory = mmap(NULL , PAGESIZE , PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS , -1 , 0);
     *shared_memory = 25;
     if(fork() == 0)
     {
         *shared_memory = 15;
         v = 80;
     }
     else
        {
                wait(NULL);
        }
     printf("not shared value v=%d\n",v);
     printf("shared value = %i\n",*shared_memory);
 }