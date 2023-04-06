/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:49:42 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/06 18:18:57 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	unset(void *cont, int fd)
{
	t_elems	*temp;
	char	**vars;
	int		i;

	(void)fd;
	i = -1;
	vars = (char **)cont;
	array(m()->env)->cmp = cmp_env;
	while (vars[++i])
	{
		temp = array(m()->env)->search(comp_var, vars[i]);
		if (temp)
		{
			array(m()->env)->remove(temp);
		}
	}
	array(m()->env)->cmp = comp_var;
	free(m()->a_env);
	m()->a_env = (char **)array(m()->env)->to_array();
	return (0);
}
