/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:15:01 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/09 18:46:24 by dcarvalh         ###   ########.fr       */
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
	m()->env = creat_array();
	while (*envp)
		array(m()->env)->add(create_cont(*envp++))->del = del_elem;
	array(m()->env)->to_array = to_array_mini;
	m()->a_env = (char **)array(m()->env)->to_array();
	shell_lvl();
	array(m()->env)->cmp = cmp_env;
	array(m()->env)->build_tree();
	array(m()->env)->cmp = comp_var;
}
