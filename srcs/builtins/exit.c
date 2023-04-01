void	free_pp(void *pp);
void	free_pp(void *pp);
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:47:30 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 15:47:52 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int s_exit(int sc)
{
    destroy_m();
    exit(sc);
}

int	ft_exit(void *cont)
{
    char **vars;
    int ret;

    vars = (char **)cont;
    if (vars[1])
    {
        cona("exit: too many arguments");
        return 1;
    }
//    printf("%ld", (long)cont);
    free_pp(cont);
    ret = (int)((long)cont);
	destroy_m();
	exit(ret);
}