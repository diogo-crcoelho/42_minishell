/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:08:13 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/06 20:17:06 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	cona(char *err)
{
    write(2, err, s().len(err, 0));
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
