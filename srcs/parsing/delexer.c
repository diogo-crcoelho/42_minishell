#include "../../incs/minishell.h"

//
// Created by dcarvalh on 3/15/23.
//
void filler(t_token *token)
{
    t_elems *tmp;
    char *clean;

    tmp = array(minishell()->cmds)->end;
    if ((IN == token->type) && !((t_cmd *)tmp->content)->fd_red[0])
        ((t_cmd *)tmp->content)->fd_red[0] = open(token->token, O_RDONLY);
    else if ((OUT == token->type))
        ((t_cmd *)tmp->content)->fd_red[1] = open(token->token, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    else if (IN != token->type)
    {
        clean = strings().join(((t_cmd *)tmp->content)->path, token->token, "");
        free(((t_cmd *)tmp->content)->path);
        ((t_cmd *)tmp->content)->path = clean;
    }
}

void delexer(void)
{
    t_elems *tmp;
    t_elems *cmds;

    tmp = array(minishell()->tokens)->begin;
    while(tmp)
    {
        array(minishell()->cmds)->add(ft_calloc(sizeof (t_cmd )));
        cmds = array(minishell()->cmds)->end;
        while (tmp && PIPE != ((t_token *)tmp->content)->type)
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

void print_cmds(void)
{
    t_elems *tmp;
    t_cmd  *ttt;

    tmp = (array(minishell()->cmds)->begin);
    while (tmp)
    {
        ttt = (t_cmd *)tmp->content;
        printf("Infile: %i\n", ttt->fd_red[0]);
        printf("Outfile: %i\n", ttt->fd_red[1]);
        printf("cmd: ");
        while (*(ttt->args))
            printf("%s ", *(ttt->args)++);
        printf("\n");
        printf("========\n");
        tmp = tmp->next;
    }
}