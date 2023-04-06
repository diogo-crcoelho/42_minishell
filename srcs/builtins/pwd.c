/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:43:29 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/04/06 16:37:47 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	pwd(void *cont, int fd)
{
	char	*str;

	(void)cont;

	str = NULL;
	str = getcwd(str, PATH_MAX);
    write(fd, str, s().len(str, 0));
    write(fd, "\n", 1);
	free(str);
	return (0);
}	
