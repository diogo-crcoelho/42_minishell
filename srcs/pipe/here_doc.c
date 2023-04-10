/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:56:23 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/09 20:28:31 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by dcarvalh on 3/26/23.
//
#include "../../incs/minishell.h"

char    *here_lines()
{
    char *tmp;
    char *var;
    char *tmp2;
    char *str;
    char *str2;

    str2 = NULL;
    tmp = get_next_line(0);
    if (!s().len(tmp, 0))
        return (NULL);
    tmp2 = tmp;
    while (*tmp && *tmp != '$')
        ++tmp;
    str = s().copy_n(tmp2, tmp - tmp2);
    if (*tmp)
    {
        str2 = str;
        var = var_state(&tmp, 0);
        str = s().join(str2, tmp, var);
        free(var);
    }
    free(tmp2);
    free(str2);
    return (str);
}


void	here_doc(t_cmd *cmd, char *eof)
{
	char	*str;

	m()->inter = 1;
	if (pipe(cmd->fd) < 0)
		s_exit(2);
	while (1)
	{
		write(1, "here_doc> ", 10);
		str = here_lines();
		if (!str && printf("\n"))
			break ;
		if (!s().equal(eof, str))
		{
			free(str);
			break ;
		}
		write(cmd->fd[1], str, s().len(str, 0));
		free(str);
	}
	if (-1 != cmd->fd_red[0])
		cmd->fd_red[0] = dup(cmd->fd[0]);
	close_pipes(cmd);
	m()->inter = 0;
	free(eof);
}
