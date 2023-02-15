#include "../../incs/minishell.h"

void	echo(char *str, int flag)
{
    if (!strings().len(str, 0))
        str = strings().copy("");
    else if(!strings().equal_n(str, "~", 1))
        str = strings().join(getenv("HOME"), &str[1], 0);
    else
        str = strings().copy(str);
    printf("%s", str);
    if (flag)
    		printf("\n");
    free (str);
}