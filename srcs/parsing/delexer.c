#include "../../incs/minishell.h"

//
// Created by dcarvalh on 3/15/23.
//
void    del_cmd(void *cmd)
{
    int i;

    i = -1;
    if (((t_cmd *)cmd)->outfile)
        free(((t_cmd *)cmd)->outfile);
    if (((t_cmd *)cmd)->infile)
        free(((t_cmd *)cmd)->infile);
    while (((t_cmd *)cmd)->args[++i])
        free(((t_cmd *)cmd)->args[i]);
    free(((t_cmd *)cmd)->path);
    free(cmd);
}

void	filler(t_token *token, t_elems *tmp)
{
    char	*clean;

	if ((IN == token->type))
    {
        ((t_cmd *)tmp->content)->infile = strings().copy(token->token);
        ((t_cmd *)tmp->content)->fd_red[0] = open(token->token, O_RDONLY);
        ((t_cmd *)tmp->content)->inf = 0;
    }
	if (OUT == token->type)
    {
        ((t_cmd *)tmp->content)->outfile = strings().copy(token->token);
        ((t_cmd *)tmp->content)->fd_red[1] = open(token->token,O_WRONLY | O_TRUNC | O_CREAT, 0644);
    }
	if (APP == token->type)
    {
        ((t_cmd *)tmp->content)->outfile = strings().copy(token->token);
        ((t_cmd *)tmp->content)->fd_red[1] = open(token->token,O_WRONLY | O_APPEND | O_CREAT, 0644);
    }
    else if (IN != token->type)
    {
        clean = strings().join(((t_cmd *)tmp->content)->path, token->token, "");
        free(((t_cmd *)tmp->content)->path);
        ((t_cmd *)tmp->content)->path = clean;
    }
}

void filler2(t_token *token)
{
//    char	*clean;
    t_elems	*tmp;

    tmp = array(minishell()->cmds)->end;
    filler(token, tmp);
//    if ()
//        ;

}
void	delexer(void)
{
	t_elems	*tmp;
	t_elems	*cmds;

	tmp = array(minishell()->tokens)->begin;
	while (tmp)
	{
		array(minishell()->cmds)->add(ft_calloc(sizeof(t_cmd)));
		cmds = array(minishell()->cmds)->end;
		while (tmp && PIPE != ((t_token *)tmp->content)->type)
		{
			filler2((t_token *)tmp->content);
			tmp = tmp->next;
		}
		if (((t_cmd *)cmds->content)->path)
			((t_cmd *)cmds->content)->args = strings().split(((t_cmd *)cmds->content)->path,
					' ');
		free(((t_cmd *)cmds->content)->path);
		if (tmp)
			tmp = tmp->next;
	}
}

void	print_cmds(void)
{
	t_elems *tmp;
	t_cmd *temp;

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