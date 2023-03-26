//
// Created by mvenanci on 2/13/23.
//

#include "../../incs/minishell.h"

void	ft_exit(int exit_status)
{
    destroy_minishell();
	exit(exit_status);
}