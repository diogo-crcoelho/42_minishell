/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:08:13 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/13 15:25:38 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	err_hand(char *err, int flag)
{
	write(2, err, s().len(err, 0));
	if (flag)
		free(err);
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

t_mini	*m(void)
{
	static t_mini	a;

	return (&a);
}

void	close_pipes(t_cmd *cmd)
{
	if (cmd->fd[0] > 2)
		close(cmd->fd[0]);
	if (cmd->fd[1] > 2)
		close(cmd->fd[1]);
}

void	del_cmd(void *cmd)
{
	int	i;

	i = -1;
	if (((t_cmd *)cmd)->outfile)
		free(((t_cmd *)cmd)->outfile);
	if (((t_cmd *)cmd)->infile)
		free(((t_cmd *)cmd)->infile);
	while (((t_cmd *)cmd)->args && ((t_cmd *)cmd)->args[++i])
		free(((t_cmd *)cmd)->args[i]);
	if (((t_cmd *)cmd)->args)
		free(((t_cmd *)cmd)->args);
	free(cmd);
}
