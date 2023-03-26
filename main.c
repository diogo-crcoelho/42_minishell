#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef 	void *(*t_func)();


int  ttt(void *t)
{
    return (long int)t;
}
int main()
{
    printf("%d\n", ttt((void *)4654316516351653));

}