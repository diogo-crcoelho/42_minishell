/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:46:10 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 15:46:45 by mvenanci         ###   ########.fr       */
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
    if (!s().equal_n(*strs, "-n", 2))
    {
        ++i;
        flag = 1;
    }
    flag = 0;
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
