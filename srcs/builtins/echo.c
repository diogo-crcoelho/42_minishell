/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:46:10 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/09 18:46:47 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	flag_check(char *str, int *next)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if ('n' != str[i])
			return (0);
	++*next;
	return (1);
}

int	echo(void *cont, int fd)
{
	int		i;
	int		flag;
	char	**strs;

	strs = (char **)cont;
	i = -1;
	flag = 0;
	if (*strs)
	{
		if (!s().equal_n(*strs, "-n", 2))
			flag = flag_check(&(*strs)[2], &i);
		while (strs[++i])
		{
			write(fd, strs[i], s().len(strs[i], 0));
			if (strs[i + 1])
				write(fd, " ", 1);
		}
	}
	if (!flag)
		write(fd, "\n", 1);
	return (0);
}
