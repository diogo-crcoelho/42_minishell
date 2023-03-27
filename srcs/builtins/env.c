/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:37:43 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/27 15:47:23 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	print_each(t_elems *elem, void *o)
{
	(void)o;
	printf("%s\n", ((t_env *)elem->cont)->total);
}

int	env(void *cont)
{
	(void)cont;
	(array(m()->env))->for_each(print_each, 0);
	return (0);
}
