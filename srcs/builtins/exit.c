//
// Created by mvenanci on 2/13/23.
//

#include "../../incs/minishell.h"

int	ft_exit(void* content)
{
	destroy_minishell();
	exit(*(int *)content);
}