/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:56:23 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/10 20:09:13 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*here_lines_cut_lines(char *str, char **tmp);

char	*here_lines(void)
{
	char	*tmp;
	char	*tmp2;
	char	*str;
	char	*str2;

	tmp = get_next_line(0);
	tmp2 = tmp;
	str = NULL;
	while (tmp && *tmp)
	{
		while (*tmp && *tmp != '$')
		{
			str2 = str;
			str = s().append(str, *tmp++);
			free(str2);
		}
		if (*tmp == '$')
			str = here_lines_cut_lines(str, &tmp);
	}
	free(tmp2);
	return (str);
}

void	here_c(int sig)
{
	(void)sig;
	write(2, "^C\n", 3);
	s_exit(130);
}

void	signal_here(void)
{
	signal(SIGINT, here_c);
	signal(SIGQUIT, SIG_IGN);
}

void	loop_here(t_cmd *cmd, char *eof)
{
	char	*str;

	close(cmd->fd[0]);
	while (1)
	{
		term_change();
		signal_here();
		write(1, "here_doc> ", 10);
		str = here_lines();
		if (!str && printf("\n"))
		{
			write(cmd->fd[1], "\0", 1);
			free(eof);
			s_exit(0);
		}
		if (!s().equal(eof, str))
		{
			close(cmd->fd[1]);
            if (cmd->fd_red[1])
                close(cmd->fd_red[1]);
			free(eof);
			free(str);
			s_exit(0);
		}
		write(cmd->fd[1], str, s().len(str, 0));
		free(str);
	}
}

void	here_doc(t_cmd *cmd, char *eof)
{
	int	pid;

	m()->inter = -1;
	if (pipe(cmd->fd) < 0)
		s_exit(2);
	pid = fork();
	if (!pid)
		loop_here(cmd, eof);
	wait(&m()->exit_status);
	m()->h = WEXITSTATUS(m()->exit_status);
	m()->exit_status = m()->h;
	if (-1 != cmd->fd_red[0])
		cmd->fd_red[0] = dup(cmd->fd[0]);
	free(eof);
	close_pipes(cmd);
	signals_hand();
}
