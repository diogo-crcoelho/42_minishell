/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:46:10 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/06 18:03:36 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	echo(void *cont, int fd)
{
	int		i;
	int		flag;
	char	**strs;

	strs = (char **)cont;
	i = -1;
	flag = 0;
	if (!*strs)
		return (0);
	if (!s().equal(*strs, "-n"))
	{
		++i;
		flag = 1;
	}
	while (strs[++i])
	{
		write(fd, strs[i], s().len(strs[i], 0));
		if (strs[i + 1])
			write(fd, " ", 1);
	}
	if (!flag)
		write(fd, "\n", 1);
	return (0);
}
