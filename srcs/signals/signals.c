/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:54:53 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/04/11 15:04:56 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <signal.h>

void	ctrl_c(int sig)
{
	(void)sig;
	m()->exit_status = 130;
	if (m()->inter > 0)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (!m()->inter)
	{
		write(2, "^C\n", 3);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_bs(int sig)
{
	(void)sig;
	if (m()->inter < 1)
		SIG_IGN ;
	else
		printf("Quit (core dumped)\n");
}

void	signals_hand(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_bs);
}

void	reset_the_terminal(void)
{
	tcsetattr(0, 0, &m()->term);
}

void	term_change(void)
{
	struct termios	termios_new;

	if (tcgetattr(0, &m()->term))
	{
		perror("");
		return ;
	}
	if (atexit(reset_the_terminal))
	{
		perror("");
		return ;
	}
	termios_new = m()->term;
	termios_new.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_new))
	{
		perror("");
		return ;
	}
}
