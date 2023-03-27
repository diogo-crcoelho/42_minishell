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

#include "../../incs/minishell.h"
void exe_buil(t_cmd *cmd)
{
	t_tree *ll;
	t_built *tt;

	ll = array(m()->b)->search_tree(NULL, (void *)cmd->args[0]);
    if (!ll)
        return ;
    for (int i = 0; cmd->args[i]; i++)
        printf("%s", cmd->args[i]);

    printf("\n");
    tt = (t_built *)ll->cont;
    m()->exit_status = tt->b(&cmd->args[1]);

}


int	built(t_elems *elem)
{
	if (array(m()->cmds)->size <= 1)
	{
		exe_buil((t_cmd *)elem->cont);
		return 1;
	}
	return 0;
}