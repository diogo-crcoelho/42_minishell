#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef 	void *(*t_func)();

int teste(void *tt)
{
    printf("%ld", (long)tt);
}

int main()
{
    long a = 12;
    t_func t = (void *)a;

    printf("%ld", LONG_MAX);
}