/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:53:00 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/04/12 15:15:46 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	check_var_validity(char c)
{
	if (!c || c == ' ' || c == '|')
		return (0);
	return (1);
}

char	*var_state_cut_lines(char **str, char *temp)
{
	char	*var;

	while (**str && ft_isalnum(**str))
		(*str)++;
	temp = s().copy_n(temp, *str - temp);
	if (array(m()->env)->search_tree(NULL, temp))
		var = s().copy(((t_env *)array(m()->env) \
			->search_tree(array(m()->env)->root, temp) \
			->cont)->splitted[1]);
	else
		var = ft_calloc(2);
	free(temp);
	return (var);
}

int	add_space(char *s)
{
	if (*s == '|' || !*s)
		return (0);
	else if (!array(m()->tokens)->end || \
		((t_token *)array(m()->tokens)->end->cont)->type == PIPE)
		return (0);
	return (1);
}