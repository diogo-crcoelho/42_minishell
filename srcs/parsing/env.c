/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:50:24 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 15:51:05 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	comp_var(void *c1, void *c2)
{
	char	*in_tree;
	char	*out_tree;

	in_tree = ((t_env *)c1)->splitted[0];
	out_tree = c2;
	return (s().equal(in_tree, out_tree));
}
