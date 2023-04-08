/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:06:45 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/08 17:02:11 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	del_symbol(void *cont)
{
	free(((t_dict *)cont)->key);
	free(((t_dict *)cont)->comp);
	free(cont);
}

t_dict	*c_dict(char *key, int value)
{
	t_dict	*new;

	new = ft_calloc(sizeof(t_dict));
	new->key = key;
	new->value = value;
	new->comp = init_comp(value);
	return (new);
}

void	init_symbols_line_cut(char *key)
{
	key[0] = '<';
	key[1] = 0;
	((t_dict *)(array(m()->symbols)->add(c_dict(s().copy(key),
						IN))->cont))->state = infile_state;
	array(m()->symbols)->end->del = del_symbol;
	key[0] = '>';
	((t_dict *)(array(m()->symbols)->add(c_dict(s().copy(key),
						OUT))->cont))->state = infile_state;
	array(m()->symbols)->end->del = del_symbol;
	key[0] = '"';
	((t_dict *)(array(m()->symbols)->add(c_dict(s().copy(key),
						STR))->cont))->state = str_state;
	array(m()->symbols)->end->del = del_symbol;
	key[0] = 39;
	((t_dict *)(array(m()->symbols)->add(c_dict(s().copy(key),
						LSTR))->cont))->state = lstr_state;
	array(m()->symbols)->end->del = del_symbol;
	key[0] = '$';
	((t_dict *)(array(m()->symbols)->add(c_dict(s().copy(key),
						VAR))->cont))->state = var_state;
	array(m()->symbols)->end->del = del_symbol;
	array(m()->symbols)->build_tree();
	array(m()->symbols)->cmp = comp_symbols_search;
	free(key);
}

void	init_symbols(void)
{
	char	*key;

	key = ft_calloc(3);
	m()->symbols = creat_array();
	array(m()->symbols)->cmp = comp_symbols_build;
	key[0] = '<';
	key[1] = '<';
	((t_dict *)(array(m()->symbols)->add(c_dict(s().copy(key),
						HERE))->cont))->state = heredoc_state;
	array(m()->symbols)->end->del = del_symbol;
	key[0] = '>';
	key[1] = '>';
	((t_dict *)(array(m()->symbols)->add(c_dict(s().copy(key),
						APP))->cont))->state = infile_state;
	array(m()->symbols)->end->del = del_symbol;
	init_symbols_line_cut(key);
}
