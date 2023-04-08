/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:08:13 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/08 17:07:16 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	cona(char *err)
{
	write(2, err, s().len(err, 0));
	m()->exit_status = 2;
}

void	free_pp(void *pp)
{
	char	**freed;
	int		i;

	i = -1;
	freed = (char **)pp;
	while (freed && freed[++i])
		free(freed[i]);
	if (freed)
		free(freed);
	freed = NULL;
}

void	close_pipes(t_cmd *cmd)
{
	close(cmd->fd[0]);
	close(cmd->fd[1]);
}