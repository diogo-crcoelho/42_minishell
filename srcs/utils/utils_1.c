/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:08:13 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 16:08:28 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void cona(char *err)
{
//    long xx;
//
//    xx = (long)m()->exit_status;
    write(2, err, s().len(err, 0));
//    ft_exit((void *)xx);
}
