/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:27:27 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/06 18:58:37 by mvenanci         ###   ########.fr       */
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
	while (((t_cmd *)cmd)->args && ((t_cmd *)cmd)->args[++i])
		free(((t_cmd *)cmd)->args[i]);
	if (((t_cmd *)cmd)->args)
		free(((t_cmd *)cmd)->args);
	free(cmd);
}

void	filler_cut_lines(t_token *token, t_elems *tmp)
{
	int	open_flags;

	if (OUT == token->type)
			open_flags = O_TRUNC;
	else
		open_flags = O_APPEND;
	if (((t_cmd *)tmp->cont)->fd_red[1])
		free(((t_cmd *)tmp->cont)->outfile);
	((t_cmd *)tmp->cont)->outfile = s().copy(token->token);
	((t_cmd *)tmp->cont)->fd_red[1] = \
		open(token->token, O_WRONLY | open_flags | O_CREAT, 0644);
	if (!(((t_cmd *)tmp->cont)->err) && --((t_cmd *)tmp->cont)->ord)
		((t_cmd *)tmp->cont)->err = errno;
}

void	filler(t_token *token, t_elems *tmp, int *flag)
{
	if ((IN == token->type) && ++(*flag) && \
		-1 != ((t_cmd *)tmp->cont)->fd_red[0])
	{
		if (((t_cmd *)tmp->cont)->fd_red[0])
			free(((t_cmd *)tmp->cont)->infile);
		((t_cmd *)tmp->cont)->infile = s().copy(token->token);
		((t_cmd *)tmp->cont)->fd_red[0] = open(token->token, O_RDONLY);
		if (!(((t_cmd *)tmp->cont)->err) && ++((t_cmd *)tmp->cont)->ord)
			((t_cmd *)tmp->cont)->err = errno;
	}
	if ((OUT == token->type || APP == token->type) && ++(*flag) && \
		-1 != ((t_cmd *)tmp->cont)->fd_red[1])
		filler_cut_lines(token, tmp);
}

void	filler2(t_token *token, int j)
{
	char	*clean;
	int		flag;
	t_elems	*tmp;

	flag = 0;
	tmp = array(m()->cmds)->end;
	filler(token, tmp, &flag);
	if (HERE == token->type)
		here_doc((t_cmd *)tmp->cont, s().append(token->token, '\n'));
	else if (SPC == token->type)
		return ;
	else if (!flag)
	{
		if (j)
			clean = s().join(((t_cmd *)tmp->cont)->path, token->token, "\e");
		else
			clean = s().join(((t_cmd *)tmp->cont)->path, token->token, "");
		free(((t_cmd *)tmp->cont)->path);
		((t_cmd *)tmp->cont)->path = clean;
	}
}

int	check_syntax(void)
{
	t_elems	*tmp;
	int		f;

	f = 0;
	tmp = array(m()->tokens)->begin;
	if (tmp && PIPE == ((t_token *)tmp->cont)->type)
		f = 1;
	if (array(m()->tokens)->end && \
		PIPE == ((t_token *)array(m()->tokens)->end->cont)->type)
		f = 1;
	while (tmp)
	{
		if (PIPE == ((t_token *)tmp->cont)->type)
		{
			if (tmp->next && PIPE == ((t_token *)tmp->next->cont)->type)
			{
				f = 1;
				break ;
			}
		}
		tmp = tmp->next;
	}
	if (f && printf("Syntax error...\n"))
		return (1);
	return (0);
}

void	delexer(void)
{
	t_elems	*tmp;
	t_elems	*cmds;
	int		j;

	tmp = array(m()->tokens)->begin;
	if (!check_syntax())
	{
		while (tmp)
		{
			array(m()->cmds)->add(ft_calloc(sizeof(t_cmd)))->del = del_cmd;
			cmds = array(m()->cmds)->end;
			while (tmp && PIPE != ((t_token *)tmp->cont)->type)
			{
				j = (tmp->prev && SPC == ((t_token *)tmp->prev->cont)->type);
				filler2((t_token *)tmp->cont, j);
				tmp = tmp->next;
			}
			if (((t_cmd *)cmds->cont)->path)
				((t_cmd *)cmds->cont)->args = \
					s().split(((t_cmd *)cmds->cont)->path, 27);
			free(((t_cmd *)cmds->cont)->path);
			if (tmp)
				tmp = tmp->next;
		}	
	}
	m()->c_count = (array(m()->cmds)->size);
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
