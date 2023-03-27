/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:43:16 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 16:07:06 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

unsigned long	hash(char *str)
{
	unsigned long	hash;

	hash = 5381;
	while (*str)
	{
		hash = (hash << 5) + hash + *str;
		str++;
	}
	return (hash);
}

int	comp_symbols_build(void *c1, void *c2)
{
	char	*in_tree;
	char	*out_tree;

	in_tree = ((t_dict *)c1)->key;
	out_tree = ((t_dict *)c2)->key;
	return (hash(in_tree) - hash(out_tree));
}

int	comp_symbols_search(void *c1, void *c2)
{
	char	*in_tree;
	char	out_tree[3];

	out_tree[1] = 0;
	out_tree[2] = 0;
	in_tree = ((t_dict *)c1)->key;
	if (((char *)c2)[0] == '<' && ((char *)c2)[1] == '<')
		out_tree[1] = '<';
	else if (((char *)c2)[0] == '>' && ((char *)c2)[1] == '>')
	{
		out_tree[1] = '>';
	}
	out_tree[0] = ((char *)c2)[0];
	return (hash(in_tree) - hash(out_tree));
}

void	print_dict(t_elems *elem, void *o)
{
	t_dict	*cont;

	(void)o;
	cont = (t_dict *)elem->cont;
	printf("\n%s--%d\n", cont->key, cont->value);
}

int	*init_comp(int type)
{
	int	*comp;

	comp = ft_calloc(10 * sizeof(int));
	if (type == VAR || type == LSTR)
		return (comp);
	comp[0] = 1;
	if (type == STR)
		return (comp);
	comp[3] = 1;
	comp[4] = 1;
	return (comp);
}
