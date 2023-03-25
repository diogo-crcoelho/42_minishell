//
// Created by dcarvalh on 3/20/23.
//

#include "../../incs/minishell.h"

int	dup_and_close(t_cmd *cmd)
{
    if (dup2(cmd->fd_red[1], 1) < 0)
            return (-1);
    close(cmd->fd_red[1]);
    if (dup2(cmd->fd_red[0], 0) < 0)
        return (-1);
    if (cmd->fd_red[0])
        close(cmd->fd_red[0]);
    return (1);
}

void	error_handle(char *cmd)
{
    if (!*cmd)
        write(2, "Permission denied\n", 18);
    else
    {
        write(2, "command not found: ", 19);
        while (*cmd)
        {
            write(2, cmd, 1);
            cmd++;
        }
        write(2, "\n", 1);
    }
}

void parse_paths(t_cmd *cmd)
{
    char *teste;
    char **paths;
    int  i;

    i = 0;
    paths = strings().split(getenv("PATH"), ':');
    while (paths[i])
    {

        teste = strings().join(paths[i++], cmd->args[0], "/");
        if (access(teste, F_OK) == 0)
        {
//            array(paths)->destroy();
            cmd->path = teste;
            return;
        }
        free(teste);
    }
    cmd->path = cmd->args[0];
}
//void	execute(t_cmd *elem)
//{
//    t_cmd	*cmd;
//    int		fd_out;
//
//    if (!elem->next)
//    {
//        while (ac--)
//            waitpid(-1, &fd_in, 0);
//        return ;
//    }
//    fd_out = cmd->fd[1];
//    cmd->pid = fork();
//    if (cmd->pid == -1)
//        exit(0);
//    else if (!cmd->pid)
//    {
//        if (dup_and_close(fd_in, fd_out) >= 0)
//            execve(cmd->path, cmd->args, env);
//        error_handle(cmd->path);
//        exit(127);
//    }
//    close(fd_in);
//    close(fd_out);
//    execute(elem->next, cmd->fd[0], env, ac);
//}

int 	treat_files(t_cmd *cmd)
{
    int	fds[2];

    if (-1 == cmd->fd_red[0]) {
        perror(cmd->infile);
        pipe(fds);
        close(fds[1]);
        return (fds[0]);
    }
    if (-1 == cmd->fd_red[1]) {
        printf("Couldn't open %s\n", cmd->outfile);
        exit(1);
    }
    return -42;
}

// void	execute(t_elems *elem)
// {
//     t_cmd	*cmd;

//     cmd = (t_cmd *)elem->content;
//     parse_paths(cmd);
//     if (-1 == cmd->fd_red[0])
//         cmd->fd_red[0] = treat_files(0, cmd->infile);
//     if (-1 == cmd->fd_red[1])
//         treat_files(1, cmd->outfile);
// //    if (!elem->next)
// //    {
// //        while (array(minishell()->cmds)->size--)
// //            waitpid(-1, &minishell()->exit_status, 0);
// //        return ;
// //    }
// char **tmp = (char **)array(minishell()->env)->to_array();
//     cmd->pid = fork();
//     if (-1 == cmd->pid)
//         exit(-1);
//     else if (!cmd->pid)
//     {
// //        if (dup_and_close(cmd) >= 0)
// //        {
//             minishell()->inter = 1;
//             execve(cmd->path, cmd->args, tmp);
// 			for (int i = 0; tmp[i]; i++)
// 				free(tmp[i]);
// 			free(tmp);
//             error_handle(cmd->path);
//             exit(127);
// //        }

//     }
//     minishell()->inter = 0;
//     close(cmd->fd_red[0]);
//     close(cmd->fd_red[1]);
//     waitpid(-1, 0, 0);
// //    execute(elem->next);
// }
//void	pipex(int ac, char **av, char **env)
//{
//    int		fd_in;
//    int		fd_out;
//    int		flag;
//
//    if (ac > 4)
//    {
//        flag = 2;
//        if (!strings().equal_n(av[1], "here_doc", 9))
//        {
//            parse_here_doc(&fd_in, *(av + 2), &flag);
//            fd_out = open(av[ac - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
//        }
//        else
//        {
//            fd_in = open(av[1], O_RDONLY);
//            if (fd_in == -1 && flag++ && fd_in++)
//                fd_in = treat_infile(av[1]);
//            fd_out = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
//        }
//        if (fd_out == -1)
//            exit(printf("Couldn't open %s\n", av[ac - 1]));
//        init_cmds(ac - flag, strings().split(getenv("PATH"), ':'), av + flag, fd_out);
//        execute(array(*cmds())->begin, fd_in, env, ac - flag);
//        array(*cmds())->destroy();
//    }
//}
void	run(t_elems *elem, char **env)
{
    t_cmd	*cmd;
    cmd = (t_cmd *)elem->content;

	if(-1 != dup2(cmd->fd_red[0], 0))
	{
		if (elem->next && !cmd->fd_red[1])
		{
			if (-1 == dup2(cmd->fd[1], 1))
				ft_exit(-1);
		}
		else if (!elem->next)
			if (cmd->fd_red[1])
				if (-1 == dup2(cmd->fd_red[1], 1))
					ft_exit(-1);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		execve(cmd->path, cmd->args, env);
	}
	ft_exit(-1);
}

void	execute(t_elems *elem)
{
    t_cmd	*cmd;

	char **tmp = (char **)array(minishell()->env)->to_array();
	while (elem)
	{
	    cmd = (t_cmd *)elem->content;
    	parse_paths(cmd);
    	treat_files(cmd);
		if (pipe(cmd->fd) < 0)
			ft_exit(1); // dont know status code
		cmd->pid = fork();
		if (-1 == cmd->pid)
			ft_exit(1);
		if (0 == cmd->pid)
			run(elem, tmp);
		else
		{
    		minishell()->inter = 0;
    		if (elem->next)
			{
				if (!((t_cmd *)elem->next->content)->fd_red[0])
					((t_cmd *)elem->next->content)->fd_red[0] = dup(cmd->fd[0]);	
			}
			elem = elem->next;
			close(cmd->fd[0]);
    		close(cmd->fd[1]);
		}
		
	}
}


void	pipex()
{
    execute(array(minishell()->cmds)->begin);
    while ((array(minishell()->cmds)->size)--)
		waitpid(-1, &minishell()->exit_status, 0);
}

