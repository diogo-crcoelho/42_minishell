#include "../../incs/minishell.h"

int unset(void *content)
{
    t_elems *temp;
    char    *var;

    var = (char *)content;
    temp = array(minishell()->env)->search(cmp, var, strings().len(var, 0));
    if (temp)
        array(minishell()->env)->remove(temp);
    return (0);
}


