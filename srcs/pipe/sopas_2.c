/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopas_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:57:36 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/06 20:10:00 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	run_cut_lines(t_cmd *cmd, t_elems *elem, int flag)
{
	if (flag)
	{
		close(cmd->fd[0]);
		if (cmd->infile || elem->prev)
			close(cmd->fd_red[0]);
		if (elem->prev)
			close(((t_cmd *)elem->prev->cont)->fd[1]);
		close(cmd->fd[1]);
		execve(cmd->path, cmd->args, m()->a_env);
		befor_exit(cmd);
	}
	else
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		free(cmd->path);
	}
}

void	run(t_elems *elem)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)elem->cont;
	if (!cmd->args || !s().len(cmd->args[0], 0))
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		s_exit(0);
	}
	parse_paths(cmd);
	if (-1 != dup2(cmd->fd_red[0], 0))
	{
		if (elem->next && !cmd->fd_red[1])
		{
			if (-1 == dup2(cmd->fd[1], 1))
				s_exit(2);
		}
		else if (!elem->next)
			if (cmd->fd_red[1])
				if (-1 == dup2(cmd->fd_red[1], 1))
					s_exit(2);
		run_cut_lines(cmd, elem, 1);
	}
	run_cut_lines(cmd, elem, 0);
	s_exit(m()->exit_status);
}

void	execute(t_elems *elem)
{
	t_cmd	*cmd;

	while (elem)
	{
		cmd = (t_cmd *)elem->cont;
		if (pipe(cmd->fd) < 0)
			s_exit(2);
		if (!built(elem))
		{
			cmd->pid = fork();
			if (-1 == cmd->pid)
				s_exit(2);
			if (0 == cmd->pid)
				run(elem);
			else
				if (elem->next && !((t_cmd *)elem->next->cont)->fd_red[0])
					((t_cmd *)elem->next->cont)->fd_red[0] = dup(cmd->fd[0]);
			built_cut_lines(cmd, elem);
		}
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		elem = elem->next;
	}
}

void	pipex(void)
{	
	int	size;

	execute(array(m()->cmds)->begin);
	size = m()->c_count;
	while (size-- > 0)
	{
		waitpid(-1, &(m()->exit_status), 0);
		m()->exit_status = WEXITSTATUS(m()->exit_status);
		// printf("--%d\n", m()->exit_status);
	}
	m()->inter = 0;
}
