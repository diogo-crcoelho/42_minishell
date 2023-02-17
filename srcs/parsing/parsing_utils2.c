//
// Created by dcarvalh on 2/16/23.
//

#include "../../incs/minishell.h"

char *expand(char *str)
{
    t_elems *teste;
    int i;

    if (!strings().equal_n(str, "~", 1))
        return strings().join(getenv("HOME"), &str[1], 0);
    else if (!strings().equal_n(str, "$", 1) && (str[1]) != '?')
    {
        i = strings().alnum(&str[1]);
        if (!i)
            i = strings().len(&str[1], 0);
        teste = array(minishell()->env)->search(cmp, str + 1, i);
        if (teste) {
            if (str[++i])
                return strings().join(((t_env *)teste->content)->splitted[1], &str[i], 0);
            return strings().copy(((t_env *)teste->content)->splitted[1]);
        }
        else
            return "";
    }
    return str;
}