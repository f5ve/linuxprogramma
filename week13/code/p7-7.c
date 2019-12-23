#include "ch07.h"
static volatile sig_atomic_t sigflag = 0;
static void sig_usr (int signo)
{
	psignal (signo, "	recieved");
}
