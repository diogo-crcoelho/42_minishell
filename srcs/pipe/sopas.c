/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:56:48 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/06 14:30:16 by dcarvalh         ###   ########.fr       */
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
		if (0 == access(teste, F_OK))
		{
			cmd->path = teste;
            free_pp(paths);
			return ;
		}
		free(teste);
	}
    free_pp(paths);
	cmd->path = s().copy(cmd->args[0]);
}

void	treat_files(t_cmd *cmd)
{
	char *err;

	if (-1 == cmd->fd_red[1] && cmd->ord < 0)
	{
		err = s().join(cmd->outfile, strerror(cmd->err), ": ");
		write(2, err, s().len(err, 0));
		write(2, "\n", 1);
		free(err);
        // printf("--%d\n", cmd->err);
		m()->exit_status = 1;
        return ;
//		s_exit(m()->exit_status);
	}
	if (-1 == cmd->fd_red[0] && cmd->ord > 0)
	{
		err = s().join(cmd->infile, strerror(cmd->err), ": ");
		write(2, err, s().len(err, 0));
		write(2, "\n", 1);
		free(err);
        // printf("--%d\n", cmd->err);
		m()->exit_status = 2;
//        s_exit(m()->exit_status);
	}
	return ;
}

void befor_exit(t_cmd *cmd)
{
    char *err = NULL;

    m()->exit_status = 127;
    if (s().contains(cmd->args[0], "/") && access(cmd->args[0], F_OK))
        err = s().join(cmd->args[0], "No such file or directory\n", ": ");
    else
    {
        if (!access(cmd->args[0], F_OK))
        {
            if (0 != access(cmd->args[0], X_OK) && --(m()->exit_status))
                err = s().join(cmd->args[0], "Permission denied\n", ": ");
            else if (s().contains(cmd->args[0], "/") && opendir(cmd->args[0]) && --m()->exit_status)
                err = s().join(cmd->args[0], "Is a directory\n", ": ");
            else
                err = s().join(cmd->args[0], "command not found\n", ": ");
        }
        else
            err = s().join(cmd->args[0], "command not found\n", ": ");
//        else

    }
    write(2, err, s().len(err, 0));
    free (err);
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
		close(cmd->fd[0]);
        close(cmd->fd_red[0]);
        if (elem->prev)
            close(((t_cmd *)elem->prev->cont)->fd[1]);
        close(cmd->fd[1]);

		execve(cmd->path, cmd->args, m()->a_env);
        befor_exit(cmd);
	}
	close(cmd->fd[0]);
	close(cmd->fd[1]);
    free(cmd->path);
	s_exit(m()->exit_status);
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
                run(elem);
		    else
			    if (elem->next)
				    if (!((t_cmd *)elem->next->cont)->fd_red[0])
					    ((t_cmd *)elem->next->cont)->fd_red[0] = dup(cmd->fd[0]);
			if (cmd->infile || elem->prev)
				close(cmd->fd_red[0]);
			if (elem->prev)
				close(((t_cmd *)elem->prev->cont)->fd[1]);
			if (cmd->outfile)
				close(cmd->fd_red[1]);
		}
		close(cmd->fd[0]);
		close(cmd->fd[1]);
        elem = elem->next;
    }
}

void	pipex(void)
{	
    int size;

	execute(array(m()->cmds)->begin);
    size = m()->c_count;
//    printf("%d\n", size);
//    printf("\n--%d\n", m()->exit_status);
	while (size-- > 0)
	{
		waitpid(-1, &(m()->exit_status), 0);
//        printf("\n--%d\n", WEXITSTATUS(m()->exit_status));
        m()->exit_status = WEXITSTATUS(m()->exit_status);
	}
	m()->inter = 0;
}
