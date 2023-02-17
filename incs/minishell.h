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
#include "structs.h"

typedef 	void	(*t_func)();
//t_func func = (void *) printf;


void    pwd();
void    env();
void    unset(char *var);
void    export(char *var);
int     cd(char *path);
void	echo(char **str, int flag);



t_mini 	*minishell(void);
void    init_minishell(char **envp);

void	del_elem(void *content);
char **env_split(char *str, char sep);

int cmp(void *cont1, void *cont2, int size);
void init_parse(const char *str);

//utils
char	**env_split(char *str, char sep);
t_env	*create_content(char *total);


void	ft_exit(int exit_status);
char *expand(char *str);



#endif