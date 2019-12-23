#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <singal.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include <errno.h>
#include "err_exit.h"
#define check_error(return_val,mag){			\
	if(return_val != 0){				\
		fprintf(stderr, "%s : %s\n",msg,strerror(return_val));\
		exit(-1);\
	}\
}
