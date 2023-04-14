/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:57:36 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/12 14:43:45 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	tmp_clear(t_cmd *cmd);

void	run_cut_lines(t_cmd *cmd, t_elems *elem, int flag)
{
	close_pipes(cmd);
	if (flag)
	{
		if (cmd->fd_red[1])
			close(cmd->fd_red[1]);
		if (cmd->fd_red[0] || elem->prev)
			close(cmd->fd_red[0]);
		if (elem->prev)
			close(((t_cmd *)elem->prev->cont)->fd[1]);
		execve(cmd->path, cmd->args, m()->a_env);
		befor_exit(cmd);
	}
	else
	{
		close(cmd->fd_red[1]);
		free(cmd->path);
	}
}

void	run(t_elems *elem)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)elem->cont;
	if (!cmd->args) // || !s().len(cmd->args[0], 0))
		tmp_clear(cmd);
	parse_paths(cmd);
	if (!cmd->fd_red[0] || -1 != dup2(cmd->fd_red[0], 0))
	{
		if (elem->next && !cmd->fd_red[1])
		{
			if (-1 == dup2(cmd->fd[1], 1))
				s_exit(1);
		}
		else if (cmd->fd_red[1] || !elem->next)
			if (cmd->fd_red[1])
				if (-1 == dup2(cmd->fd_red[1], 1))
					s_exit(1);
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
		second_parse(cmd);
		if (pipe(cmd->fd) < 0)
			s_exit(2);
		if (!built(elem))
		{
			cmd->pid = fork();
			if (-1 == cmd->pid)
				s_exit(2);
			if (0 == cmd->pid)
				run(elem);
			else if (elem->next && !((t_cmd *)elem->next->cont)->fd_red[0])
				((t_cmd *)elem->next->cont)->fd_red[0] = dup(cmd->fd[0]);
			built_cut_lines(cmd, elem);
		}
		close_pipes(cmd);
		if (cmd->fd_red[0] > 2)
			close(cmd->fd_red[0]);
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
		if (WIFEXITED(m()->exit_status))
			m()->exit_status = WEXITSTATUS(m()->exit_status);
		else
			m()->exit_status = WTERMSIG(m()->exit_status) + 128;
	}
	m()->inter = 0;
}
