//link with -lpthread
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
/*
Thread routine - argument must be supplied with void *
Read data from Stdin and write in a file
*/
void *write_stdin(void *ptr)
{
    int fd;
    char buffer[1024];
    printf("Enter the message to be sent\n");
    fgets(buffer,sizeof(buffer),stdin);
    fd = open("sensor_data.txt",O_RDWR | O_CREAT, S_IRWXU);
    write(fd,buffer,strlen(buffer)+1);
}
/*
Thread routine - II
Publish the data to the topic /home/sensor/dht22 from the file sensor_data.txt
*/

void *publish_data(void *ptr)
{
	sleep(20);
	const char *command = "mosquitto_pub -t home/sensor/dht22 -h localhost -p 1883 -f ./sensor_data.txt -d ";
	system(command);
	return 0;
}
void main()
{
        pthread_t thread1, thread2;
        int ret1 = pthread_create(&thread1,NULL,write_stdin,NULL);
        int ret2 = pthread_create(&thread2,NULL,publish_data,NULL);
	/*
	pthread_join will block the calling thread i.e. main thread
	to complete the execution of thread which is passed as a first arugument
	Note:
	if pthread_join will not be used : It may happen that main thread has complete its execution and some statement doesn't
	yield the results e.g. printf takes time to send buffer data to console
	*/
        pthread_join(thread1,NULL);
        pthread_join(thread2, NULL);
        //return 0;

}
