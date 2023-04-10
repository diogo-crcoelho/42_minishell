/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopas_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:26:15 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/04/10 20:34:21 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tmp_clear(t_cmd *cmd)
{
	close_pipes(cmd);
	if (cmd->fd_red[0])
		close(cmd->fd_red[0]);
	if (cmd->fd_red[1])
		close(cmd->fd_red[1]);
	s_exit(0);
}
