/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:37:43 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/04/11 12:00:41 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	print_each(t_elems *elem, void *o)
{
	char	*err;
	int		fd;

	(void)o;
	fd = (int)((long)o);
	if (((t_env *)elem->cont)->splitted[1])
	{
		err = s().append(((t_env *)elem->cont)->total, '\n');
		write(fd, err, s().len(err, 0));
		free(err);
	}
}

int	env(void *cont, int fd)
{
	char	**vars;
	char	*err;
	long	fd1;

	fd1 = (long)fd;
	vars = (char **)cont;
	if (vars && vars[0])
	{
		err = s().join("env: ", ": No such file or directory\n", vars[0]);
		err_hand(err);
		free(err);
		return (2);
	}
	(array(m()->env))->for_each(print_each, (void *)fd1);
	return (0);
}
