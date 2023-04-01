#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


///exit atoi
//space append;
typedef 	void *(*t_func)();

int teste(void *tt)
{
    printf("%ld", (long)tt);
}

int main(int ac, char **av, char **env)
{
    long a = 12;
    t_func t = (void *)a;

    char *teste[4] = {"ls", "-l", "-a", NULL};
    execve("/usr/bin/ls", teste, env);
}