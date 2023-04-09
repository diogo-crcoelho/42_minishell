/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:08:13 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/09 18:49:22 by dcarvalh         ###   ########.fr       */
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

void	print_cmds(void)
{
	t_elems	*tmp;
	t_cmd	*temp;

	tmp = (array(m()->cmds)->begin);
	while (tmp)
	{
		temp = (t_cmd *)tmp->cont;
		printf("Infile: %i\n", temp->fd_red[0]);
		printf("Outfile: %i\n", temp->fd_red[1]);
		printf("cmd: ");
		for (int i = 0; temp->args[i]; i++)
			printf("%s -%i", temp->args[i], i);
		printf("\n");
		printf("========\n");
		tmp = tmp->next;
	}
}
