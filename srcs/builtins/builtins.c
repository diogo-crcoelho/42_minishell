/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:39:40 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 15:42:46 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
int	comp_build_tree(void *c1, void *c2)
{
    char	*in_tree;
    char	*out_tree;

    in_tree = ((t_dict *)c1)->key;
    out_tree = (char *)c2;
    return (hash(in_tree) - hash(out_tree));
}

void	del_b(void *b)
{
	free(((t_built *)b)->key);
	free(b);
}

t_built	*c_b(char *key)
{
	t_built	*new;

	new = ft_calloc(sizeof(t_built));
	new->key = key;
	return (new);
}

void	init_b(void)
{
	m()->b = creat_array();
	array(m()->b)->cmp = comp_symbols_build;
	((t_built *)array(m()->b)->add(c_b(s().copy("pwd")))->cont)->b = pwd;
	array(m()->b)->end->del = del_b;
	((t_built *)array(m()->b)->add(c_b(s().copy("env")))->cont)->b = env;
	array(m()->b)->end->del = del_b;
	((t_built *)array(m()->b)->add(c_b(s().copy("unset")))->cont)->b = unset;
	array(m()->b)->end->del = del_b;
	((t_built *)array(m()->b)->add(c_b(s().copy("export")))->cont)->b = export;
	array(m()->b)->end->del = del_b;
	((t_built *)array(m()->b)->add(c_b(s().copy("cd")))->cont)->b = cd;
	array(m()->b)->end->del = del_b;
	((t_built *)array(m()->b)->add(c_b(s().copy("echo")))->cont)->b = echo;
	array(m()->b)->end->del = del_b;
	((t_built *)array(m()->b)->add(c_b(s().copy("exit")))->cont)->b = ft_exit;
	array(m()->b)->end->del = del_b;
    array(m()->b)->build_tree();
    array(m()->b)->cmp = comp_build_tree;

}
