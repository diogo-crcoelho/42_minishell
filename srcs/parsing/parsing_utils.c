/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:31 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/08 17:01:08 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	second_parse(char *str)
{
	printf("%s\n", str);
}

void	init_parse(const char *str)
{
	char	**splitted;
	int		i;

	i = -1;
	splitted = s().split(str, '|');
	while (splitted[++i])
		second_parse(s().trim(splitted[i]));
}
