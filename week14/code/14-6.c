#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#define NUM_THREADS	8
char *messages[NUM_THREADS];
struct thread_data{
	int thread_id;
	int sum;
	char *message;
};
struct thread_data thread_data_array[NUM_THREADS];
void *PrintHello(void *threadarg){
	int taskid, sum;
	char *hello_msg;
	struct thread_data *my_data;
	sleep(1);
	my_data = (struct thread_data *) threadarg;
	taskid = my_data->sum;
	sum = my_data->sum;
	hello_msg = my_data->message;
	printf("Thread %d : %s Sum=%d\n",taskid, hello_msg, sum);
	pthread_exit(NULL);
}
int main(int argc, char *argv[]){
	pthread_t threads[NUM_THREADS];
	int *taskids[NUM_THREADS];
	int rc, t, sum;
	sum=0;
	messages[0] = "0";
	messages[1] = "1";
	messages[2] = "2";
	messages[3] = "3";
	messages[4] = "4";
	messages[5] = "5";
	messages[6] = "6";
	messages[7] = "7";
	 for(t=0;t<NUM_THREADS;t++) {
		sum = sum + t;
		thread_data_array[t].thread_id = t;
		thread_data_array[t].sum = sum;
		thread_data_array[t].message = messages[t];
		printf("createing thread %d\n",t);
		rc = pthread_create(&threads[t], NULL, PrintHello,
			(void *)&thread_data_array[t]);
		if (rc)	{
			printf("EERO,return code %d\n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);
}
