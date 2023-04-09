/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:54:47 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/09 18:54:53 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	*lstr_state(char **str, int add)
{
	int		type;
	char	*lstr;
	char	*temp;

	type = ((t_dict *)array(m()->symbols) \
	->search_tree(array(m()->symbols)->root,
				*str)->cont)->value;
	(*str)++;
	temp = *str;
	while (**str && **str != 39)
		(*str)++;
	lstr = s().copy_n(temp, *str - temp);
	if (**str)
		(*str)++;
	if (add)
		(array(m()->tokens))->add(c_token(lstr, type))->del = del_token;
	return (lstr);
}

void	*non_symbol_state_cut_lines(char *temp, char *temp_free, t_dict *symbol,
		char **str)
{
	char	*temp_free_2;

	temp_free_2 = symbol->state(str, 0);
	temp = s().join(temp, temp_free_2, "");
	free(temp_free);
	free(temp_free_2);
	return (temp);
}

void	*non_symbol_state(char **str, int add)
{
	char	*temp;
	char	*temp_free;
	t_dict	*symbol;

	temp = ft_calloc(1);
	while (**str && **str != ' ' && \
			**str != '|' && **str != '<' && **str != '>')
	{
		symbol = (t_dict *)array(m()->symbols)->search_tree(NULL, *str);
		temp_free = temp;
		if (symbol)
		{
			temp = non_symbol_state_cut_lines(temp, temp_free,
					((t_tree *)(symbol))->cont, str);
			continue ;
		}
		else
			temp = s().append(temp, **str);
		free(temp_free);
		if (!**str || !(*str)++)
			break ;
	}
	if (add)
		(array(m()->tokens))->add(c_token(temp, CMD))->del = del_token;
	return (temp);
}

int	check_validity(char *str)
{
	if (*str == '~' && (*(str + 1) == ' ' || *(str + 1) == '|' || *(str
				+ 1) == '/' || !*(str + 1)))
		return (1);
	return (0);
}

void	update_home(void)
{
	char	*home;

	home = (char *)(array(m()->env)->search_tree(0, "HOME"));
	if (home)
	{
		home = ((t_env *)((t_tree *)home)->cont)->splitted[1];
		if (!m()->home || s().equal(m()->home, home))
		{
			if (m()->home)
				free(m()->home);
			m()->home = s().copy(home);
		}
	}
}
