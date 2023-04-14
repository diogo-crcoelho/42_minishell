/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:38:25 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/04/09 19:49:00 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	exe_buil(t_elems *elem)
{
	t_cmd	*cmd;
	t_tree	*ll;
	t_built	*tt;

	cmd = (t_cmd *)elem->cont;
	if (!cmd->args || !s().len(cmd->args[0], 0))
		return (0);
	ll = array(m()->b)->search_tree(NULL, (void *)cmd->args[0]);
	if (!ll)
		return (0);
	tt = (t_built *)ll->cont;
	if (!cmd->outfile)
		cmd->fd_red[1] = 1;
	(m())->exit_status = tt->b(&cmd->args[1], cmd->fd_red[1]);
	if (cmd->outfile)
		close(cmd->fd_red[1]);
	return (1);
}

int	built_cut_lines2(t_elems *elem, int balls)
{
	if (balls && m()->c_count--)
		return (m()->exit_status);
	if (exe_buil(elem) && m()->c_count--)
		return (1);
	return (0);
}

void	pipe_built(t_elems *elem)
{
	t_cmd	*cmd;
	long	err;

	err = 0;
	cmd = (t_cmd *)elem->cont;
	if (!cmd->args || !s().len(cmd->args[0], 0))
		s_exit(2);
	if (elem->next && !cmd->fd_red[1])
	{
		if (-1 == dup2(cmd->fd[1], 1))
			s_exit(1);
	}
	else if (!elem->next)
	{
		if (cmd->fd_red[1])
			if (-1 == dup2(cmd->fd_red[1], 1))
				s_exit(1);
	}
	close_pipes(cmd);
	m()->exit_status = !exe_buil(elem);
	if (cmd->fd_red[0])
		close(cmd->fd_red[0]);
	close(cmd->fd_red[1]);
	err = m()->exit_status;
	s_exit(err);
}

void	built_cut_lines(t_cmd *cmd, t_elems *elem)
{
	if (cmd->infile || elem->prev)
		close(cmd->fd_red[0]);
//	if (elem->prev && ((t_cmd *)elem->prev->cont)->fd[1] > 2)
//		close(((t_cmd *)elem->prev->cont)->fd[1]);
	if (cmd->outfile)
		close(cmd->fd_red[1]);
}

int	built(t_elems *elem)
{
	t_cmd	*cmd;
	int		balls;

	cmd = (t_cmd *)elem->cont;
	balls = treat_files(cmd);
	m()->inter = 1;
	if (array(m()->cmds)->size <= 1)
		return (built_cut_lines2(elem, balls));
	else if (cmd->args && array(m()->b)->search_tree(NULL, cmd->args[0]))
	{
		cmd->pid = fork();
		if (-1 == cmd->pid)
			s_exit(2);
		if (0 == cmd->pid)
			pipe_built(elem);
		else if (elem->next && !((t_cmd *)elem->next->cont)->fd_red[0])
			((t_cmd *)elem->next->cont)->fd_red[0] = dup(cmd->fd[0]);
		built_cut_lines(cmd, elem);
		return (1);
	}
	return (0);
}

//array(m()->b)->search_tree(NULL, cmd->args[0]) &&