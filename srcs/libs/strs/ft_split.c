/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:09:06 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/02/09 17:29:01 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

char	**ft_split(const char *str, int sep)
{
	char		**strings;
	static int	size;
	int			i;
	char		*word;

	i = 0;
	while (*str && *str == sep)
		str++;
	while (str[i] && str[i] != sep)
		++i;
	word = NULL;
	if (i)
	{
		word = ft_calloc(i + 1);
		while (*str && *str != sep)
			*word++ = *str++;
	}
	if (*str && *str == sep  && ++size)
		strings = ft_split(str, sep);
	else
		strings = malloc((size + 1) * sizeof(char *));
	strings[size--] = word - i;
	return (strings);
}
