/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:00:37 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/06 20:15:16 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	cmp_env(void *cont1, void *cont2)
{
	char	*s1;
	char	*s2;

	s1 = ((t_env *)cont1)->splitted[0];
	s2 = ((t_env *)cont2)->splitted[0];
	return (s().equal(s1, s2));
}

int	comp_var(void *c1, void *c2)
{
	char	*in_tree;
	char	*out_tree;

	in_tree = ((t_env *)c1)->splitted[0];
	out_tree = (char *)c2;
	return (s().equal(in_tree, out_tree));
}

void	del_elem(void *cont)
{
	char	**vars;
	int		i;

	vars = ((t_env *)cont)->splitted;
	i = -1;
	free(((t_env *)cont)->total);
	while (vars[++i])
		free(vars[i]);
	free(vars);
	free(cont);
}

char	**env_split(char *str, char sep)
{
	char	**split_env;
	int		i;
	int		len;

	len = s().len(str, 0);
	i = 0;
	while (str && str[i] && str[i] != sep)
		++i;
	split_env = ft_calloc(sizeof(char *) * (2 + (i != len)));
	split_env[0] = s().copy_n(str, i);
	if (i != len)
		split_env[1] = s().copy(&str[i + 1]);
	return (split_env);
}

void	**to_array_mini(void)
{
	void	**arr;
	t_elems	*temp;
	int		i;

	arr = ft_calloc(((array(m()->env)->size + 1) * sizeof(void *)));
	temp = array(m()->env)->begin;
	i = 0;
	while (temp)
	{
		arr[i++] = ((t_env *)(temp->cont))->total;
		temp = temp->next;
	}
	return (arr);
}

