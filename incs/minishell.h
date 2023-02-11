/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:41:56 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/02/10 14:06:02 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHSELL_H
# define MINIHSELL_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../srcs/libs/list/list_utils.h"
#include "../srcs/libs/strs/ft_strings.h"

typedef 	void	(*t_func)();
//t_func func = (void *) printf;
typedef struct s_mini t_mini;

void pwd();
void env();
void init_minishell(char **envp);

t_mini 	*minishell(void);

struct s_mini{
	void	*env;
	void	*cmds;
	int 	exit_status;
	char 	*prev_path;
};


#endif