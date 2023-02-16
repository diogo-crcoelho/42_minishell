#include "../../incs/minishell.h"

void	echo(char *str, int flag)
{
    if (strings().len(str, 0))
        printf("%s", str);
    if (flag)
    		printf("\n");
}