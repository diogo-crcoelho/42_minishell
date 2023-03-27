//
// Created by dcarvalh on 3/26/23.
//
#include "minishell.h"
void	here_doc(t_cmd *cmd, char *eof)
{
    char	*str;

    if (pipe(cmd->fd) < 0)
        ft_exit ((void *)1);
    while (1)
    {
        write(1, "here_doc> ", 11);
        str = get_next_line(1);
        if (!str)
            write(1, "\n", 1);
        if (!strings().equal(eof, str))
        {
            free(str);
            break ;
        }
        write(cmd->fd[1], str, strings().len(str, 0));
        free (str);
    }
    cmd->fd_red[0] = dup(cmd->fd[0]);
    close(cmd->fd[0]);
    close(cmd->fd[1]);
	free(eof);
}

