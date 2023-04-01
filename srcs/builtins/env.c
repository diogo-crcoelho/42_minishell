/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:37:43 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/31 15:12:12 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	print_each(t_elems *elem, void *o)
{
	(void)o;
	printf("%s\n", ((t_env *)elem->cont)->total);
}



int	env(void *cont)
{
	char	**vars;
	char	*err;

	
	vars = (char **)cont;
	if (vars[0])
	{
		err = s().join("env: ", ": No such file or directory\n", vars[0]);
		cona(err);
		free(err);
		return (127);
	}
	(array(m()->env))->for_each(print_each, 0);
	return (0);
}
