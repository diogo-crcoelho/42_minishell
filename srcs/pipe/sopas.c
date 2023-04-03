/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:56:48 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/03 15:59:00 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	dup_and_close(t_cmd *cmd)
{
	if (dup2(cmd->fd_red[1], 1) < 0)
		return (-1);
	close(cmd->fd_red[1]);
	if (dup2(cmd->fd_red[0], 0) < 0)
		return (-1);
	close(cmd->fd_red[0]);
	if (cmd->fd_red[0])
		close(cmd->fd_red[0]);
	return (1);
}

void	error_handle(char *cmd)
{
	if (!*cmd)
		write(2, "Permission denied\n", 18);
	else
	{
		write(2, "command not found: ", 19);
		while (*cmd)
		{
			write(2, cmd, 1);
			cmd++;
		}
		write(2, "\n", 1);
	}
}

void	parse_paths(t_cmd *cmd)
{
	char	*teste;
	char	**paths;
	int		i;

	i = 0;
	paths = s().split(getenv("PATH"), ':');
	while (paths[i])
	{
		teste = s().join(paths[i++], cmd->args[0], "/");
		if (access(teste, F_OK) == 0)
		{
			cmd->path = teste;
			return ;
		}
		free(teste);
	}
    free_pp(paths);
	cmd->path = cmd->args[0];
}

int	treat_files(t_cmd *cmd)
{
	int	fds[2];

	if (-1 == cmd->fd_red[0])
	{
		perror(cmd->infile);
		pipe(fds);
		close(fds[1]);
		return (fds[0]);
	}
	if (-1 == cmd->fd_red[1])
	{
		printf("Couldn't open %s\n", cmd->outfile);
		s_exit(2);
	}
	return (-42);
}

void	run(t_elems *elem)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)elem->cont;
	if (!cmd->args || !s().len(cmd->args[0], 0))
		s_exit(2);
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
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		m()->inter = 1;
		execve(cmd->path, cmd->args, m()->a_env);
	}
	s_exit(2);
}

void	execute(t_elems *elem)
{
	t_cmd	*cmd;

	while (elem)
	{
		cmd = (t_cmd *)elem->cont;
		if (pipe(cmd->fd) < 0) {
            s_exit(2);
        } // dont know status code
        if (!built(elem))
        {
            cmd->pid = fork();
            if (-1 == cmd->pid)
                s_exit(2);
            if (0 == cmd->pid)
            {
                treat_files(cmd);
                run(elem);
            }
		    else
		    {
			    m()->inter = 0;
			    if (elem->next)
			    {
				    if (!((t_cmd *)elem->next->cont)->fd_red[0])
					    ((t_cmd *)elem->next->cont)->fd_red[0] = dup(cmd->fd[0]);
					close(cmd->fd[0]);
        			close(cmd->fd[1]);
			    }
		    }
        }
        elem = elem->next;
        
    }
}

void	pipex(void)
{	
    int size;

    size = (array(m()->cmds)->size);
	execute(array(m()->cmds)->begin);
	while (size--)
		waitpid(-1, &m()->exit_status, 0);
}
