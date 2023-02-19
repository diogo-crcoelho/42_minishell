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
void    init_symbols(void);
void    print_dict(t_elems *elem, void *o);

void	del_elem(void *content);
char    **env_split(char *str, char sep);

int cmp(void *cont1, void *cont2, int size);
void init_parse(const char *str);

//utils
char	**env_split(char *str, char sep);
t_env	*create_content(char *total);

//tokens
void    init_tokens(void);
t_token *c_token(char *s, int type);

//states
void    *infile_state(char **s, int add);
void    *var_state(char **s, int add);
char    *aux_state(char **s, char *lex);

//symbols
int     comp_symbols_search(void *c1, void *c2);
int     comp_symbols_build(void *c1, void *c2);

void	ft_exit(int exit_status);
char    *expand(char *str);



#endif