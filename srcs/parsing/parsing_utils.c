/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:31 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/12 14:56:15 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	second_parse(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->args && cmd->args[++i])
		if ('\b' == *(cmd->args[i]))
			*(cmd->args[i]) = 0;
}

void	cutter(char *str, int type)
{
	if (!*str && type != VAR)
		*str = '\b';
}

void	history(t_elems *elem, char *str)
{
	t_cmd	*cmd;

	while (elem)
	{
		cmd = (t_cmd *)elem->cont;
		if (cmd->fd_red[0] || cmd->fd_red[1] || \
			cmd->args || *cmd->args)
		{
			add_history(str);
			return ;
		}
		elem = elem->next;
	}
	return ;
}
