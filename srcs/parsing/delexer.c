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
        while (6 != ((t_token *)tmp->content)->type)
        {

        }
    }
}