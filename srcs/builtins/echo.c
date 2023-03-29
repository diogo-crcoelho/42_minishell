/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:46:10 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/29 18:50:37 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	echo(void *cont)
{
	int		i;
	int		flag;
	char	**strs;

    strs = (char **)cont;
    i = -1;
    flag = 0;
	if (!*strs)
		return (0);
    if (!s().equal(*strs, "-n"))
    {
        ++i;
        flag = 1;
    }
    while (strs[++i])
    {
        printf("%s", strs[i]);
        if (strs[i + 1])
            printf(" ");
    }
    if (!flag)
        printf("\n");
    return (0);
}
