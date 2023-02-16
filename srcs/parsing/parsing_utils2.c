//
// Created by dcarvalh on 2/16/23.
//

#include "../../incs/minishell.h"

char *expand(char *str)
{
    char *tmp;
    t_env *teste;
    int i;

    if (!strings().equal_n(str, "~", 1))
        return strings().join(getenv("HOME"), &str[1], 0);
    else if (!strings().equal_n(str, "$", 1))
    {
        i = strings().alnum(&str[1]);
        if (!i)
            i = strings().len(&str[1], 0);
        tmp = strings().copy_n(&str[1], i);
        fprintf(stderr, "%s-->", tmp);
        teste = (t_env *)array(minishell()->env)->search(cmp, tmp, i)->content;
        if (teste) {
            if (str[++i])
                return strings().join(teste->splitted[1], &str[i], 0);
            return strings().copy(teste->splitted[1]);
        }
    }
    return str;
}