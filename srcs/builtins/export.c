
#include "../../incs/minishell.h"

//falta verificar se o bicho existe

int export(char *var)
{
    array(minishell()->env)->add(strings().split(var, '='));
    return (0);
}