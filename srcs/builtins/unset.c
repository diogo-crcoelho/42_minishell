/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:49:42 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 23:07:35 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	unset(void *cont)
{
	t_elems	*temp;
	char	**vars;
	int		i;

	i = -1;
	vars = (char **)cont;
	while (vars[++i])
	{
		temp = array(m()->env)->search(cmp, vars[i], s().len(vars[i], 0));
		if (temp)
			array(m()->env)->remove(temp);
	}
	return (0);
}


