/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopas_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:57:36 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 15:58:04 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	execute(t_elems *elem)
{
	t_cmd	*cmd;
	char	**tmp;

	tmp = (char **)array(m()->env)->to_array();
	while (elem)
	{
		cmd = (t_cmd *)elem->cont;
		treat_files(cmd);
		if (pipe(cmd->fd) < 0)
			ft_exit((void *)1);
		cmd->pid = fork();
		if (-1 == cmd->pid)
			ft_exit((void *)1);
		if (0 == cmd->pid)
			run(elem, tmp);
		else
		{
			m()->inter = 0;
			if (elem->next)
			{
				if (!((t_cmd *)elem->next->cont)->fd_red[0])
					((t_cmd *)elem->next->cont)->fd_red[0] = dup(cmd->fd[0]);
			}
			elem = elem->next;
			close(cmd->fd[0]);
			close(cmd->fd[1]);
		}
	}
}

void	pipex(void)
{
	execute(array(m()->cmds)->begin);
	while ((array(m()->cmds)->size)--)
		waitpid(-1, &m()->exit_status, 0);
}