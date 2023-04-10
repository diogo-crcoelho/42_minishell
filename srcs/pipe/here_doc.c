/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:56:23 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/10 17:06:02 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by dcarvalh on 3/26/23.
//
#include "../../incs/minishell.h"

char    *here_lines()
{
    char *tmp;
    char *var;
    char *tmp2;
    char *str;
    char *str2;

    str2 = NULL;
    tmp = get_next_line(0);
    if (!s().len(tmp, 0))
        return (NULL);
    tmp2 = tmp;
    while (*tmp && *tmp != '$')
        ++tmp;
    str = s().copy_n(tmp2, tmp - tmp2);
    if (*tmp)
    {
        str2 = str;
        var = var_state(&tmp, 0);
        str = s().join(str2, tmp, var);
        free(var);
    }
    free(tmp2);
    free(str2);
    return (str);
}

void here_c(int sig)
{
    if (SIGINT == sig)
    {
        write(2, "\n", 1);
        s_exit(130);
    }
    if (SIGQUIT == sig)
        SIG_IGN ;
}

void    signal_here()
{
    signal(SIGINT, here_c);
    signal(SIGQUIT, here_c);
}

void    loop_here(t_cmd *cmd, char *eof)
{
    char	*str;
    close(cmd->fd[0]);
    while (1)
    {
        term_change();
        signal_here();
        write(1, "here_doc> ", 10);
        str = get_next_line(0);
        if (!str && printf("\n")){
            write(cmd->fd[1], "\0", 1);
            s_exit(0) ;
        }
        if (!s().equal(eof, str))
        {
            close(cmd->fd[1]);
            free(str);
            s_exit(0) ;
        }
        write(cmd->fd[1], str, s().len(str, 0));
        free(str);
    }
}
void	here_doc(t_cmd *cmd, char *eof)
{
    int pid;

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
    close_pipes(cmd);
    signals_hand();
	free(eof);
}
