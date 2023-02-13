
#include "../../incs/minishell.h"

//falta verificar se o bicho existe

int cmp(void *cont1, void *cont2, int size)
{
    int	i;
    char *str1;
    char *str2;

    str1 = ((t_env *)cont1)->splitted[0];
    str2 = (char *)cont2;
    i = -1;
    if (str1 && str2)
        while (++i < size && (str1[i] || str2[i]))
            if (str1[i] != str2[i])
                return ((unsigned char )str1[i] - (unsigned char )str2[i]);
    return (0);
}

void export(char *var)
{
    t_elems *temp;
    char    **splitted;

    splitted = env_split(var, '=');
    temp = array(minishell()->env)->search(cmp, splitted[0], strings().len(var, 0));
    if (!temp)
        array(minishell()->env)->add(splitted)->del = del_elem;
    else
    {
        free(((char **)temp->content)[1]);
        ((char **)temp->content)[1] = splitted[1];
        free(splitted[0]);
        free(splitted);
    }
}