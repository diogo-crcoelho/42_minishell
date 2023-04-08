/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:56:05 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/08 17:01:28 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && '\n' != str[i])
		i++;
	return ((i + ('\n' == str[i])));
}

static char	*ft_strjoin(char *str1, char *str2)
{
	char	*ret;
	size_t	i;

	ret = ft_calloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (str1 && str1[++i])
		ret[i] = str1[i];
	i += (!str1);
	while (*str2)
	{
		ret[i++] = *str2;
		if ('\n' == *str2++)
			break ;
	}
	ret[i] = 0;
	if (str1)
		free(str1);
	return (ret);
}

static int	next_line(char *stash)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (stash[++i])
	{
		if ('\n' == stash[i])
		{
			stash[i++] = 0;
			j = 0;
			break ;
		}
		stash[i] = 0;
	}
	while (stash[i] && j > -1)
	{
		stash[j++] = stash[i];
		stash[i++] = 0;
	}
	return (j);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	stash[101];
	size_t		i;

	i = -1;
	if (read(fd, 0, 0) < 0)
	{
		while (stash[++i])
			stash[i] = 0;
		return (NULL);
	}
	line = NULL;
	while (*stash || read(fd, stash, 100) > 0)
	{
		line = ft_strjoin(line, stash);
		if (-1 != next_line(stash))
			break ;
	}
	return (line);
}
