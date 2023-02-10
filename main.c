#include <unistd.h>

int main()
{
	char **args;
	args[0] = "bash";
	args[1] = (void *)0;
	execve("/usr/bin/bash", args, (void *)0);
}