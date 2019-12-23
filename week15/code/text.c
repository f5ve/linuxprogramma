#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
 
#define PRODUCER_NUM 3 //生产者数目
#define CONSUMER_NUM 3 //消费者数目
#define POOL_SIZE	 5  //缓冲池大小
#define COUNT_LIMIT  5	
int pool[POOL_SIZE];	//缓冲区
int readp=0;	//缓冲池读取指针
int writep=0; //缓冲池写入指针
sem_t	room_sem;		//同步信号信号量，表示缓冲区有可用空间
sem_t	product_sem;		//同步信号量，表示缓冲区有可用产品
pthread_mutex_t mutex;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_count_t count_threshold_cy;
void producer_fun(void *arg)
{
	while (1)
	{
		sleep(2);
		sem_wait(&room_sem);		//若无空间等待消费者唤醒
		pthread_mutex_lock(&mutex);	//生产者往缓冲池中写入数据并加锁
		pool[writep] = 1;				//1表示占用座位
		writep = (writep + 1) % POOL_SIZE;	//writep右移一格,若为末端则移到始端
		printf("producer %d write to pool\n", (int)arg);
		printf("pool size is %d\n",(writep-readp+POOL_SIZE)%POOL_SIZE);
		pthread_mutex_unlock(&mutex);	//写入完毕并解锁
		sem_post(&product_sem);		//唤醒等待的消费者
	}
}
 
 
void consumer_fun(void *arg)
{
	while (1)
	{
		int data;
		sleep(2);
		sem_wait(&product_sem);
		pthread_mutex_lock(&mutex);
		//消费者从缓冲池读取数据
		data = pool[readp];
		readp= (readp+ 1) % POOL_SIZE;
		printf("consumer %d read from pool\n", (int)arg);
		printf("pool size is %d\n",(writep-readp+POOL_SIZE)%POOL_SIZE);
		pthread_mutex_unlock(&mutex);
		sem_post(&room_sem);
	}
}
 
int main()
{
	pthread_t producer_id[PRODUCER_NUM];
	pthread_t consumer_id[CONSUMER_NUM];
	pthread_mutex_init(&mutex, NULL);	//初始化互斥量
	int ret = sem_init(&room_sem, 0, POOL_SIZE-1);	//初始化信号量room_sem为缓冲池大小
	if (ret != 0)
	{
		printf("sem_init error");
		exit(0);
	}
	ret = sem_init(&product_sem, 0, 0);	//初始化信号量product_sem为0，开始时缓冲池中没有数据
	if (ret != 0)
	{
		printf("sem_init error");
		exit(0);
	}
	for (int i = 0; i < PRODUCER_NUM; i++)
	{
		//创建生产者线程
		ret =pthread_create(&producer_id[i], NULL, producer_fun, (void*)i);
		if (ret != 0)
		{
			printf("producer_id error");
			exit(0);
		}
	}
	for (int i = 0; i < CONSUMER_NUM; i++)
	{
		//创建消费者线程
		ret = pthread_create(&consumer_id[i], NULL, consumer_fun, (void*)i);
		if (ret != 0)
		{
			printf("consumer_id error");
			exit(0);
		}
	}
	for(int i=0;i<PRODUCER_NUM;i++)
	{
		pthread_join(producer_id[i],NULL);
	}

	for(int i=0;i<CONSUMER_NUM;i++)
	{
		pthread_join(consumer_id[i],NULL);
	}
 
	exit(0);
}
