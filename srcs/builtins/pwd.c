/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:43:29 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/27 15:49:36 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	pwd(void *cont)
{
	char	str[PATH_MAX];

	(void)cont;
	printf("%s\n", getcwd(str, PATH_MAX));
	return (0);
}
