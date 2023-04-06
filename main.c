#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "incs/minishell.h"


///exit atoi
//space append;
//typedef 	void *(*t_func)();

char **cone()
{
    char **a = s().split("aaa aaa aaa aaa", ' ');
    return (a);
}


int main(void)
{
    char **a = cone();
    char *b = a[0];
    free(a);
    exit(1);
}

