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

void	create_env(char **envp)
{
	*get_env() = creat_array();
	while (*envp)
		array(*get_env())->add(strings().split(*envp++, '='))->del = del_elem;
}
