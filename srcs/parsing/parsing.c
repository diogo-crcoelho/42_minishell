//
// Created by mvenanci on 2/10/23.
//

#include "../../incs/minishell.h"

void	del_elem(void *content)
{
	char	**vars;
	int 	i;

	vars = (char **)content;
	i = -1;

    while (vars[++i])
        free(vars[i]);
    free(vars);
}

char **env_split(char *str, char sep)
{
    char **split_env;
    int i;
    int len;

    len = strings().len(str, 0);
    i = 0;
    while (str && str[i] && str[i] != sep)
        ++i;
    split_env = ft_calloc(sizeof(char *) * (2 + (i != len)));
    split_env[0] = strings().copy_n(str, i);
    if (i != len)
        split_env[1] = strings().copy(&str[i + 1]);
    return (split_env);
}


void	create_env(char **envp)
{
	minishell()->env = creat_array();
	while (*envp)
        array(minishell()->env)->add(env_split(*envp++, 61))->del = del_elem;
}

void init_minishell(char **envp)
{
	create_env(envp);
}
