/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:56:23 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/01 19:29:47 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by dcarvalh on 3/26/23.
//
#include "../../incs/minishell.h"

void	here_doc(t_cmd *cmd, char *eof)
{
	char	*str;

	if (pipe(cmd->fd) < 0)
		s_exit(2);
	while (1)
	{
		write(1, "here_doc> ", 10);
		str = get_next_line(1);
		if (!str)
			break ;
		if (!s().equal(eof, str))
		{
			free(str);
			break ;
		}
		write(cmd->fd[1], str, s().len(str, 0));
		free (str);
	}
	cmd->fd_red[0] = dup(cmd->fd[0]);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	free(eof);
}

