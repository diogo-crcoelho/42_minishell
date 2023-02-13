//
// Created by mvenanci on 2/13/23.
//

#include "../../incs/minishell.h"

void	ft_exit(int exit_status)
{
	array(minishell()->env)->destroy();
	exit(exit_status);
}