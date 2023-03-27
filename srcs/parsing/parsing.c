/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:26:19 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 15:42:57 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	init_m(char **envp)
{
	create_env(envp);
	m()->cmds = creat_array();
	init_tokens();
	init_symbols();
	init_b();
}
