//
// Created by mvenanci on 2/10/23.
//

#include "../../incs/minishell.h"

void	del_elem(void *content)
{
	char	**vars;
	int 	i;

	vars = ((t_env *)content)->splitted;
	i = -1;

//	acho que nao precisa desse free, confirmar
//	free(((t_env *)content)->total);
    while (vars[++i])
        free(vars[i]);
    free(vars);
	free(content);
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

t_env	*create_content(char *total)
{
	t_env	*content;

	content = ft_calloc(sizeof(t_env));
	content->total = total;
	content->splitted = env_split(total, '=');
	return (content);
}

void	create_env(char **envp)
{
	minishell()->env = creat_array();
	while (*envp)
        array(minishell()->env)->add(create_content(*envp++))->del = del_elem;
}

void init_minishell(char **envp)
{
	create_env(envp);
}
