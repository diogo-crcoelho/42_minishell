/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:15:01 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/06 20:15:19 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_env	*create_cont(char *total)
{
	t_env	*cont;

	cont = ft_calloc(sizeof(t_env));
	cont->splitted = env_split(total, '=');
	cont->total = s().copy(total);
	return (cont);
}

void	create_env(char **envp)
{
	char	str[PATH_MAX];

	m()->env = creat_array();
	(m())->prev_path = s().copy(getcwd(str, PATH_MAX));
	while (*envp)
		array(m()->env)->add(create_cont(*envp++))->del = del_elem;
	array(m()->env)->to_array = to_array_mini;
	array(m()->env)->cmp = cmp_env;
	array(m()->env)->build_tree();
	array(m()->env)->cmp = comp_var;
	m()->a_env = (char **)array(m()->env)->to_array();
}