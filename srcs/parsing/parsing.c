//
// Created by mvenanci on 2/10/23.
//

#include "../../incs/minishell.h"

void	init_minishell(char **envp)
{
	create_env(envp);
	minishell()->cmds = creat_array();
	init_tokens();
	init_symbols();
    init_builtins();

}
