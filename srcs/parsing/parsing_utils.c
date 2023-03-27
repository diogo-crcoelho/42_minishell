/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:31 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 15:55:33 by mvenanci         ###   ########.fr       */
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
