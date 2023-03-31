/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:27:27 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/31 14:56:57 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	del_cmd(void *cmd)
{
	int	i;

	i = -1;
	if (((t_cmd *)cmd)->outfile)
		free(((t_cmd *)cmd)->outfile);
	if (((t_cmd *)cmd)->infile)
		free(((t_cmd *)cmd)->infile);
	while (((t_cmd *)cmd)->args[++i])
		free(((t_cmd *)cmd)->args[i]);
	free(((t_cmd *)cmd)->args);
	// free(((t_cmd *)cmd)->path);
	free(cmd);
}

void	filler(t_token *token, t_elems *tmp, int *flag)
{
	if ((IN == token->type) && ++(*flag))
	{
		((t_cmd *)tmp->cont)->infile = s().copy(token->token);
		((t_cmd *)tmp->cont)->fd_red[0] = open(token->token, O_RDONLY);
	}
	if (OUT == token->type && ++(*flag))
	{
		((t_cmd *)tmp->cont)->outfile = s().copy(token->token);
		((t_cmd *)tmp->cont)->fd_red[1] = \
			open(token->token, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	if (APP == token->type && ++(*flag))
	{
		((t_cmd *)tmp->cont)->outfile = s().copy(token->token);
		((t_cmd *)tmp->cont)->fd_red[1] = \
			open(token->token, O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
}

void	filler2(t_token *token)
{
	char	*clean;
	int		flag;
	t_elems	*tmp;

	flag = 0;
	tmp = array(m()->cmds)->end;
	filler(token, tmp, &flag);
	if (HERE == token->type)
		here_doc((t_cmd *)tmp->cont, s().append(token->token, '\n'));
	if (SPC == token->type)
		return ;
	else if (!flag && IN != token->type)
	{
		clean = s().join(((t_cmd *)tmp->cont)->path, token->token, "\e");
		free(((t_cmd *)tmp->cont)->path);
		((t_cmd *)tmp->cont)->path = clean;
	}
}

void	delexer(void)
{
	t_elems	*tmp;
	t_elems	*cmds;

	tmp = array(m()->tokens)->begin;
	while (tmp)
	{
		array(m()->cmds)->add(ft_calloc(sizeof(t_cmd)))->del = del_cmd;
		cmds = array(m()->cmds)->end;
		while (tmp && PIPE != ((t_token *)tmp->cont)->type)
		{
			filler2((t_token *)tmp->cont);
			tmp = tmp->next;
		}
		if (((t_cmd *)cmds->cont)->path)
			((t_cmd *)cmds->cont)->args = s().\
				split(((t_cmd *)cmds->cont)->path,
					27);
		free(((t_cmd *)cmds->cont)->path);
		if (tmp)
			tmp = tmp->next;
	}
}

void	print_cmds(void)
{
	t_elems	*tmp;
	t_cmd	*temp;
	tmp = (array(m()->cmds)->begin);
	while (tmp)
	{
		temp = (t_cmd *)tmp->cont;
		printf("Infile: %i\n", temp->fd_red[0]);
		printf("Outfile: %i\n", temp->fd_red[1]);
		printf("cmd: ");
		for (int i = 0; temp->args[i]; i++)
			printf("%s ", temp->args[i]);
		printf("\n");
		printf("========\n");
		tmp = tmp->next;
	}
}
