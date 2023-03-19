/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:43:16 by mvenanci          #+#    #+#             */
/*   Updated: 2023/02/20 15:43:20 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

unsigned long hash(char *str)
{
    unsigned long   hash;

    hash = 5381;
    while(*str)
    {
        hash = (hash << 5) + hash + *str;
        str++;
    }
    return (hash);
}

int     comp_symbols_build(void *c1, void *c2)
{
	char    *in_tree;
	char    *out_tree;

	in_tree = ((t_dict *)c1)->key;
	out_tree = ((t_dict *)c2)->key;
    return (hash(in_tree) - hash(out_tree));
}

int     comp_symbols_search(void *c1, void *c2)
{
	char    *in_tree;
	char    out_tree[3];
//	int     ret_val;
//
    out_tree[1] = 0;
    out_tree[2] = 0;
	in_tree = ((t_dict *)c1)->key;
	if (((char *)c2)[0] == '<' && ((char *)c2)[1] == '<')
		out_tree[1] = '<';
	out_tree[0] = ((char *)c2)[0];
    return (hash(in_tree) - hash(out_tree));
}

void    print_dict(t_elems *elem, void *o)
{
	(void)o;
	t_dict *cont;

	cont = (t_dict *)elem->content;
	printf("\n%s--%d\n", cont->key, cont->value);
}

int *init_comp(int type)
{
    int *comp;

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

t_dict  *c_dict(char *key, int value)
{
	t_dict  *new;

	new = ft_calloc(sizeof(t_dict));
	new->key = key;
	new->value = value;
    new->comp = init_comp(value);
	return (new);
}

void    init_symbols(void)
{
	char    *key;

	key = ft_calloc(3);
    minishell()->symbols = creat_array();
    array(minishell()->symbols)->cmp = comp_symbols_build;
    key[0] = '<';
    key[1] = '<';
	((t_dict *)(array(minishell()->symbols)->add(c_dict(strings().copy(key), HERE))->content))->state = var_state;
	key[0] = '<';
	key[1] = 0;
	((t_dict *)(array(minishell()->symbols)->add(c_dict(strings().copy(key), IN))->content))->state = infile_state;
	key[0] = '>';
	((t_dict *)(array(minishell()->symbols)->add(c_dict(strings().copy(key), OUT))->content))->state = infile_state;
	key[0] = '"';
	((t_dict *)(array(minishell()->symbols)->add(c_dict(strings().copy(key), STR))->content))->state = str_state;
	key[0] = 39;
	((t_dict *)(array(minishell()->symbols)->add(c_dict(strings().copy(key), LSTR))->content))->state = lstr_state;
	key[0] = '$';
	((t_dict *)(array(minishell()->symbols)->add(c_dict(strings().copy(key), VAR))->content))->state = var_state;
	array(minishell()->symbols)->build_tree();
    array(minishell()->symbols)->cmp = comp_symbols_search;
	free(key);
}