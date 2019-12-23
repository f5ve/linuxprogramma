#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <stdlib.h>
#define err_exit(MESSAGE)(
		perror(MESSAGE),
		exit(1)
		)
struct sendval{
   int n;
   int s;
};
#define NUM 4
