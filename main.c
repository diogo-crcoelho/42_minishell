#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef 	void *(*t_func)();



int main()
{
    t_func f = (void *);
    f("");

}