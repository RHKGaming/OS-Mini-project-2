#include "types.h"
#include "stat.h"
#include "user.h"

// Running system call firstpart()
int main(void)
{
	printf(1, "I am a process with ID: %d\n", getpid());
	exit();
}
