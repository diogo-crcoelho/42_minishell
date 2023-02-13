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

#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>
//#include "pipex.h"
#include "../srcs/libs/list/list_utils.h"
#include "../srcs/libs/strs/ft_strings.h"

typedef 	void	(*t_func)();
//t_func func = (void *) printf;
typedef struct s_mini t_mini;
typedef struct s_cmd t_cmd;
typedef struct s_env t_env;

void    pwd();
void    env();
void    unset(char *var);
void    export(char *var);

t_mini 	*minishell(void);
void    init_minishell(char **envp);

void	del_elem(void *content);
char **env_split(char *str, char sep);

int cmp(void *cont1, void *cont2, int size);
void init_parse(const char *str);

//utils
char	**env_split(char *str, char sep);
t_env	*create_content(char *total);
struct s_mini{
	void	*env;
	void	*cmds;
	int 	exit_status;
	char 	*prev_path;
};

struct s_env{
	char	*total;
	char	**splitted;
};


struct s_cmd{
	char	*path;
	char	**args;
	int		fd[2];
	int		pid;
};


#endif