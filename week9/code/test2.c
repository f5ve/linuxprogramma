#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

static int k = 200;

int main()
{
	int g = 100;
	pid_t id = vfork();
	if(id == 0)
	{
			k++;
			g++;
			printf("child,running first...\ng=%d\n&g=%p\nk=%d\n&k=%p\n",g,&g,k,&k);
			sleep(1);
			exit(0);

	}
	else
	{
		k++;
		g++;
		printf("father,running second...\ng=%d\n&g=%p\nk=%d\n&k=%p\n",g,&g,k,&k);
	}
	return 0;
}
