#include "lib.h"
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
int main()
{
	int b[100];
	int a[10]={324,8,-9,5,0,3454,234,-987,100000,12};
	void *handle;
	int (*f2)(),(*f3)();
	void (*f4)();
	char* error;
	handle = dlopen("/home/rlk/linuxprogram/week6/code/dynamiclib/lib1/libdynamic.so",RTLD_LAZY);
	if(!handle)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);
	}
	f2 = dlsym(handle,"max");
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);
	}
	f3 = dlsym(handle,"sum");
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);
	}
	f4 = dlsym(handle,"urand");
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);
	}
	printf("max=%d\n",f2(a,10));
	printf("sum=%d\n",f3(a,10));
	f4(b,100);
	return 0;
}

