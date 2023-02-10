#include <unistd.h>
#include <stdlib.h>
int main()
{
	char **args;
	args = malloc(2 * sizeof(char *));
	args[0] = "bash";
	args[1] = (void *)0;
	execve("/usr/bin/bash", args, (void *)0);
}