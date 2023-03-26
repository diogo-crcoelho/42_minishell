/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:54:53 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/26 16:56:26 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <signal.h>

void	ctrl_c(int sig)
{
	(void)sig;
	if (minishell()->inter)
	{
		minishell()->exit_status = 130;
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
	//	rl_redisplay();
}

void	signals_hand(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_bs);
}