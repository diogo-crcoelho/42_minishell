/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:56:48 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/06 20:08:20 by mvenanci         ###   ########.fr       */
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

int	treat_files(t_cmd *cmd)
{
	char	*err;

	if (-1 == cmd->fd_red[1] && cmd->ord < 0)
	{
		err = s().join(cmd->outfile, strerror(cmd->err), ": ");
		write(2, err, s().len(err, 0));
		write(2, "\n", 1);
		free(err);
		m()->exit_status = 1;
		return (1);
	}
	if (-1 == cmd->fd_red[0] && cmd->ord > 0)
	{
		err = s().join(cmd->infile, strerror(cmd->err), ": ");
		write(2, err, s().len(err, 0));
		write(2, "\n", 1);
		free(err);
		m()->exit_status = 1;
		return (1);

	}
	return (0);
}

void	befor_exit(t_cmd *cmd)
{
	char	*err;

	err = NULL;
	m()->exit_status = 127;
	if (s().contains(cmd->args[0], "/") && access(cmd->args[0], F_OK))
		err = s().join(cmd->args[0], "No such file or directory\n", ": ");
	else
	{
		if (!access(cmd->args[0], F_OK))
		{
			if (0 != access(cmd->args[0], X_OK) && --(m()->exit_status))
				err = s().join(cmd->args[0], "Permission denied\n", ": ");
			else if (s().contains(cmd->args[0], "/") && \
				opendir(cmd->args[0]) && --m()->exit_status)
				err = s().join(cmd->args[0], "Is a directory\n", ": ");
			else
				err = s().join(cmd->args[0], "command not found\n", ": ");
		}
		else
			err = s().join(cmd->args[0], "command not found\n", ": ");
	}
	write(2, err, s().len(err, 0));
	free (err);
}
