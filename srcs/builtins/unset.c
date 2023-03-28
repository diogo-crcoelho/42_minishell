/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:49:42 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/28 15:48:43 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	unset(void *cont)
{
	t_elems *temp;
	char	**vars;
	int		i;

	i = -1;
	vars = (char **)cont;
	while (vars[++i])
	{
		// array(m()->env)->cmp = cmp_env;
		temp = array(m()->env)->search(comp_var, vars[i]);
		if (temp)
			array(m()->env)->remove(temp);
	}
	free(m()->a_env);
	m()->a_env = (char **)array(m()->env)->to_array();
	return (0);
}
