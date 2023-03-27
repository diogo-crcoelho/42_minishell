/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:27:27 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 15:50:17 by mvenanci         ###   ########.fr       */
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
	free(((t_cmd *)cmd)->path);
	free(cmd);
}

void	filler(t_token *token, t_elems *tmp)
{
	if ((IN == token->type))
	{
		((t_cmd *)tmp->cont)->infile = s().copy(token->token);
		((t_cmd *)tmp->cont)->fd_red[0] = open(token->token, O_RDONLY);
	}
	if (OUT == token->type)
	{
		((t_cmd *)tmp->cont)->outfile = s().copy(token->token);
		((t_cmd *)tmp->cont)->fd_red[1] = \
			open(token->token, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	if (APP == token->type)
	{
		((t_cmd *)tmp->cont)->outfile = s().copy(token->token);
		((t_cmd *)tmp->cont)->fd_red[1] = \
			open(token->token, O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
}

void	filler2(t_token *token)
{
	char	*clean;
	t_elems	*tmp;

	tmp = array(m()->cmds)->end;
	filler(token, tmp);
	if (HERE == token->type)
		here_doc((t_cmd *)tmp->cont, s().append(token->token, '\n'));
	else if (IN != token->type)
	{
		clean = s().join(((t_cmd *)tmp->cont)->path, token->token, "");
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
		array(m()->cmds)->add(ft_calloc(sizeof(t_cmd)));
		cmds = array(m()->cmds)->end;
		while (tmp && PIPE != ((t_token *)tmp->cont)->type)
		{
			filler2((t_token *)tmp->cont);
			tmp = tmp->next;
		}
		if (((t_cmd *)cmds->cont)->path)
			((t_cmd *)cmds->cont)->args = s().\
				split(((t_cmd *)cmds->cont)->path,
					' ');
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
		while ((temp->args) && *(temp->args))
			printf("%s ", *(temp->args)++);
		printf("\n");
		printf("========\n");
		tmp = tmp->next;
	}
}
