#include "../../incs/minishell.h"

//
// Created by dcarvalh on 3/15/23.
//
void filler(t_token *token)
{
    t_elems *tmp;
    char *clean;

    tmp = array(minishell()->cmds)->end;
    if ((1 == token->type) && !((t_cmd *)tmp->content)->fd_red[0])
        ((t_cmd *)tmp->content)->fd_red[0] = open(token->token, O_RDONLY);
    else if ((2 == token->type))
        ((t_cmd *)tmp->content)->fd_red[1] = open(token->token, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    else if (1 != token->type)
    {
        clean = strings().join(((t_cmd *)tmp->content)->path, token->token, " ");
        free(((t_cmd *)tmp->content)->path);
        ((t_cmd *)tmp->content)->path = clean;
    }
}

void delexer()
{
    t_elems *tmp;
    t_elems *cmds;

    tmp = array(minishell()->tokens)->begin;
    while(tmp)
    {
        array(minishell()->cmds)->add(ft_calloc(sizeof (t_cmd )));
        cmds = array(minishell()->cmds)->end;
        while (tmp && 6 != ((t_token *)tmp->content)->type)
        {
            filler(((t_token *)tmp->content));
            tmp = tmp->next;
        }
        ((t_cmd *)cmds->content)->args = strings().split(((t_cmd *)cmds->content)->path, ' ');
        free(((t_cmd *)cmds->content)->path);
        if (tmp)
            tmp = tmp->next;
    }
}
