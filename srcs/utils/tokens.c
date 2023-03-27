/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:07:27 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 16:07:44 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	del_token(void *token)
{
	free(((t_token *)token)->token);
	free(token);
}

t_token	*c_token(char *s, int type)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token));
	new->token = s;
	new->type = type;
	return (new);
}

int	comp_token(void *c1, void *c2)
{
	char	*in_tree;
	char	*out_tree;

	in_tree = ((t_token *)c1)->token;
	out_tree = (char *)c2;
	return (s().equal(in_tree, out_tree));
}

void	init_tokens(void)
{
	m()->tokens = creat_array();
	array(m()->tokens)->build_tree();
	array(m()->tokens)->cmp = comp_token;
}
