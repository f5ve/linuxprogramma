#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	int g_val = 100;
	pid_t id = vfork();
	if(id == 0)
	{
			g_val++;
			printf("child,running first...%d:%p\n",g_val,&g_val);
			sleep(1);
			exit(0);

	}
	else
	{
		printf("father,running second...%d:%p\n",g_val,&g_val);
	}
	return 0;
}
