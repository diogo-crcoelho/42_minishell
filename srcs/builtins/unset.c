/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:49:42 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/09 18:47:08 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	unset_cut(char *vars)
{
	char	*err;

	if (!s().len(vars, 0) || s().alnum(vars) || \
		!(__isalpha(vars[0])))
	{
		err = s().join("unset: ", ": not a valid identifier\n", vars);
		cona(err);
		free(err);
		array(m()->env)->cmp = comp_var;
		return (1);
	}
	return (0);
}

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
		if (unset_cut(vars[i]))
			return (1);
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
