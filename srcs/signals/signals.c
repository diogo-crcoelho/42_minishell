/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:54:53 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/27 16:00:47 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <signal.h>

void	ctrl_c(int sig)
{
	(void)sig;
	if (m()->inter)
	{
		m()->exit_status = 130;
		return ;
	}
	write(2, "^C\n", 3);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	ctrl_bs(int sig)
{
	if (SIGQUIT == sig)
		SIG_IGN;
}

void	signals_hand(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_bs);
}