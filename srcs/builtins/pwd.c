/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:43:29 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/02/10 14:05:55 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int pwd(void* content)
{
	char	str[PATH_MAX];

    (void)content;
	printf("%s\n", getcwd(str, PATH_MAX));
    return (0);
}
