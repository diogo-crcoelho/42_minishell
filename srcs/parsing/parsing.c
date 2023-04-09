/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:26:19 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/09 18:58:59 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	shell_lvl(void)
{
	t_elems	*temp;
	long	lvl;
	char	*var;
	char	*var2;
	char	**tmp;

	temp = array(m()->env)->search(comp_var, "SHLVL");
	if (!temp)
	{
		tmp = s().split("SHLVL=1", 0);
		export(tmp, 0);
		free_pp(tmp);
		return ;
	}
	lvl = (s_atoi(((t_env *)temp->cont)->splitted[1]));
	var = ft_itoa(lvl + 1);
	var2 = s().join("SHLVL", var, "=");
	tmp = s().split(var2, 0);
	export(tmp, 0);
	free_pp(tmp);
	free(var);
	free(var2);
}

void	init_m(char **envp)
{
	create_env(envp);
	m()->cmds = creat_array();
	init_tokens();
	init_symbols();
	init_b();
}
