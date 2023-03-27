/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:49:42 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 15:49:54 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	unset(void *cont)
{
	t_elems	*temp;
	char	*var;

	var = (char *)cont;
	temp = array(m()->env)->search(cmp, var, s().len(var, 0));
	if (temp)
		array(m()->env)->remove(temp);
	return (0);
}


