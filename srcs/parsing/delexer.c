//
// Created by dcarvalh on 3/15/23.
//
#include "../../incs/minishell.h"

void delexer()
{
    t_elems *tmp;
    t_token *teste;
    t_elems  *cmds;

    tmp = array(minishell()->tokens)->begin;
//    cmds = array(minishell()->cmds)->begin;
    (void)cmds;
    while(tmp)
    {
        teste = (t_token *)tmp->content;
        if (6 != teste->type)
            printf("%s--%i\n", teste->token, teste->type);
        tmp = tmp->next;
    }
}