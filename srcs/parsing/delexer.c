#include "../../incs/minishell.h"

//
// Created by dcarvalh on 3/15/23.
//
void filler(t_token *token, int flag) // 01000 para trunc 02000 para appedn
{
    t_cmd *cmd;
    char *clean;

    cmd = array(minishell()->cmds)->end->content;
    if (IN == token->type)
    {
        cmd->infile = strings().copy(token->token);
        cmd->fd_red[0] = open(token->token, O_RDONLY);
    }
    else if (OUT == token->type || APP == token->type)
    {
        cmd->outfile = strings().copy(token->token);
        cmd->fd_red[1] = open(token->token, O_WRONLY | flag | O_CREAT, 0644);
    }
//    else if ((BLTIN == token->type))
//        (tmp->bin = estrutra_bin;
    else
    {
        clean = strings().join(cmd->path, token->token, "");
        free(cmd->path);
        cmd->path = clean;
    }
}

void delexer(void)
{
    t_elems *tmp;
    t_elems *cmds;

    tmp = array(minishell()->tokens)->begin;
    while(tmp)
    {
        array(minishell()->cmds)->add(ft_calloc(sizeof (t_cmd)));
        cmds = array(minishell()->cmds)->end;
        while (tmp && PIPE != ((t_token *)tmp->content)->type)
        {
            filler((t_token *)tmp->content, 0);
            tmp = tmp->next;
        }
        if (((t_cmd *)cmds->content)->path)
            ((t_cmd *)cmds->content)->args = strings().split(((t_cmd *)cmds->content)->path, ' ');
        free(((t_cmd *)cmds->content)->path);
        if (tmp)
            tmp = tmp->next;
    }

}

void print_cmds(void)
{
    t_elems *tmp;
    t_cmd  *temp;

    tmp = (array(minishell()->cmds)->begin);
    while (tmp)
    {
        temp = (t_cmd *)tmp->content;
        printf("Infile: %i\n", temp->fd_red[0]);
        printf("Outfile: %i\n", temp->fd_red[1]);
        printf("cmd: ");
        while ((temp->args) && *(temp->args))
            printf("%s ", *(temp->args)++);
        printf("\n");
        printf("========\n");
        tmp = tmp->next;
    }
}