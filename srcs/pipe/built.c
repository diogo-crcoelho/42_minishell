/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:38:25 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/27 16:10:14 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void exe_buil(t_cmd *cmd)
{
	t_elems *ll;
	t_built *tt;

	ll = array(minishell()->builtins)->begin;
	while (ll)
	{
		tt = (t_built *)ll->content;
		if (!strings().equal(cmd->args[0], tt->key))
		{
			minishell()->exit_status = tt->builtin(&cmd->args[1]);
			return ;
		}	
		ll = ll->next;
	}
}


int	built(t_elems *elem)
{
	if (array(minishell()->cmds)->size <= 1)
	{
		exe_buil((t_cmd *)elem->content);
		elem = elem->next;
		return 1;
	}
	return 0;
}