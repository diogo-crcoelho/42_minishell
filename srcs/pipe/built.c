/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:38:25 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/31 16:39:25 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
int exe_buil(t_cmd *cmd)
{
	t_tree *ll;
	t_built *tt;

	if (!cmd->args || !s().len(cmd->args[0], 0))
		return (0);
	ll = array(m()->b)->search_tree(NULL, (void *)cmd->args[0]);
    if (!ll)
        return 0;
    tt = (t_built *)ll->cont;
    m()->exit_status = tt->b(&cmd->args[1]);
	return 1;
}

void	pipe_built(t_elems *elem)
{
	t_cmd	*cmd;
    long    err;

    err = 0;
	cmd = (t_cmd *)elem->cont;
	if (!cmd->args || !s().len(cmd->args[0], 0))
		ft_exit((void *)-1);
	if (-1 != dup2(cmd->fd_red[0], 0))
	{
		if (elem->next && !cmd->fd_red[1])
		{
			if (-1 == dup2(cmd->fd[1], 1))
				ft_exit((void *)-1);
		}
		else if (!elem->next)
			if (cmd->fd_red[1])
					if (-1 == dup2(cmd->fd_red[1], 1))
					ft_exit((void *)-1);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		m()->inter = 1;
		if (!cmd->args || !s().len(cmd->args[0], 0))
			ft_exit((void *)-1);
		m()->exit_status = exe_buil(cmd);
        err = m()->exit_status;
	}
	ft_exit ((void *)err);
}

int	built(t_elems *elem)
{
	t_cmd *cmd;

	cmd = (t_cmd *)elem->cont;
	if (array(m()->cmds)->size <= 1)
		return (exe_buil((t_cmd *)elem->cont));
	else if (array(m()->b)->search_tree(NULL, (void *)cmd->args[0]))
	{
	    cmd->pid = fork();
	    if (-1 == cmd->pid)
		    ft_exit((void *)1);
		if (0 == cmd->pid)
            pipe_built(elem);
		else
		{
		    m()->inter = 0;
		    if (elem->next)
			{
		    	if (!((t_cmd *)elem->next->cont)->fd_red[0])
		    	((t_cmd *)elem->next->cont)->fd_red[0] = dup(cmd->fd[0]);
			}
		}
		return (1);
	}
	return(0);
}