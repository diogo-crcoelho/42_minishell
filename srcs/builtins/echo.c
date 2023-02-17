#include "../../incs/minishell.h"

void	echo(char **strs, int flag)
{
    int i;

    i = -1;
    while(strs[++i])
        printf("%s", strs[i]);
    if (flag)
    		printf("\n");
}