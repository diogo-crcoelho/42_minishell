#include "../../incs/minishell.h"

void unset(char *var)
{
    t_elems *temp;

    temp = array(minishell()->env)->search(cmp, var, strings().len(var));
    if (temp)
        array(minishell()->env)->remove(temp);
}


