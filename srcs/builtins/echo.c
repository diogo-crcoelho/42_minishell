#include "../../incs/minishell.h"

int	echo(void *content)
{
    int     i;
    int     flag;
    char    **strs;

    strs = (char **)content;
    i = -1;
    flag = 0;
    if (!strings().equal_n(*strs, "-n", 2))
    {
        ++i;
        flag = 1;
    }
    while(strs[++i])
    {
        printf("%s", strs[i]);
        if (strs[i + 1])
            printf(" ");
    }
    if (!flag)
        printf("\n");
    return (0);
}
