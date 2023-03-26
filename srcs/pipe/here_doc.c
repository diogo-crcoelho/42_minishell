//
// Created by dcarvalh on 3/26/23.
//
void	make_here_env(int argc, char **argv, t_envs *env)
{
    char	*str;

    env->outfile = argv[argc - 1];
    env->files[1] = open(env->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
    if (env->files[1] < 0)
        err_handle(env->outfile, 1);
    if (pipe((*env->cmds)->fd) < 0)
        exit (1);
    while (1)
    {
        write(1, "here_doc> ", 11);
        str = get_next_line(1);
        if (!str)
            write(1, "\n", 1);
        if (ft_strcmp(str, argv[2]) == 10)
        {
            free(str);
            break ;
        }
        write((*env->cmds)->fd[1], str, ft_strlen(str));
        free (str);
    }
    (*env->cmds)->fdopen = dup((*env->cmds)->fd[0]);
    close_pipes((*env->cmds)->fd);
}

