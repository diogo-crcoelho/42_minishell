#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef 	void *(*t_func)();


char *ttt(void *t)
{
    char **test = (char **)t;
    while (*test)
    {
        printf("%s\n", *test++);
    }
}
int main()
{
//    char *test[] = { "1", "2", NULL};
    t_func a = (void *){

    };
    t_func func = (void *) write;
    t_func tt = (void *)ttt;
}