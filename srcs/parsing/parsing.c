/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:26:19 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/06 23:13:14 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	init_m(char **envp)
{
	t_tree *temp;
	long	lvl;
	char	*var;
	char	*var2;
	char	**tmp;

	create_env(envp);
	temp =  array(m()->env)->search_tree(NULL, "SHLVL");
	lvl = s_atoi(((t_env *)temp->cont)->splitted[1]);
	var = ft_itoa(lvl + 1);
	var2 = s().join("SHLVL", var, "=");
	tmp = s().split(var2, 0);
	export(tmp, 0);
	free_pp(tmp);
	free(var);
	free(var2);
	m()->cmds = creat_array();
	init_tokens();
	init_symbols();
	init_b();
	printf("%s\n", ((char *)(array(m()->env)->search_tree(0, "SHLVL"))));
}
