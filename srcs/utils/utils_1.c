/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:08:13 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/28 15:25:07 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void cona(char *err)
{
//    long xx;
//
//    xx = (long)m()->exit_status;
    write(2, err, s().len(err, 0));
//    ft_exit((void *)xx);
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
