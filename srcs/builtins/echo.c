#include "../../incs/minishell.h"

int	echo(void *content)
{
    int     i;
    int     flag;
    char    **strs;

    strs = (char **)content;
    i = -1;
    flag = 0;
    if (!strings().equal(*strs, "-n"))
    {
        ++i;
        flag = 1;
    }
    while(strs[++i])
        printf("%s", strs[i]);
    if (!flag)
        printf("\n");
    return (0);
}
