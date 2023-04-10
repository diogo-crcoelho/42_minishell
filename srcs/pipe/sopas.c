/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:56:48 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/09 18:45:58 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
	paths = (char **)array(m()->env)->search_tree(NULL, "PATH");
	if (paths)
		paths = s().split(((t_env *)((t_tree *)paths)->cont)->splitted[1], ':');
	while (paths && paths[i])
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
		if (cmd->fd_red[0] > 0)
			close(cmd->fd_red[0]);
		err = s().join(cmd->outfile, strerror(cmd->err), ": ");
		write(2, err, s().len(err, 0));
		write(2, "\n", 1);
		free(err);
		m()->exit_status = 1;
		return (1);
	}
	else if (-1 == cmd->fd_red[0] && cmd->ord > 0)
	{
		if (cmd->fd_red[1] > 0)
			close(cmd->fd_red[1]);
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
    DIR     *dir;

    dir = opendir(cmd->args[0]);
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
			else if (s().contains(cmd->args[0], "/") && dir && --m()->exit_status)
				err = s().join(cmd->args[0], "Is a directory\n", ": ");
			else
				err = s().join(cmd->args[0], "command not found\n", ": ");
		}
		else
			err = s().join(cmd->args[0], "command not found\n", ": ");
	}
    closedir(dir);
	write(2, err, s().len(err, 0));
	free(err);
}
