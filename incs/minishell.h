/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:41:56 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/26 16:55:07 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHSELL_H
# define MINIHSELL_H

# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <unistd.h>
//#include "pipex.h"
#include "../srcs/libs/list/list_utils.h"
#include "../srcs/libs/strs/ft_strings.h"
#include "structs.h"

typedef 	void	(*t_func)();
//t_func func = (void *) printf;

//general
unsigned long hash(char *str);

//builtins
void    init_builtins(void);
int     pwd(void* content);
int     env(void* content);
int     unset(void *content);
int     export(void* content);
int     cd(void *path);
int 	echo(void *content);
int	    ft_exit(void* content);


t_mini 	*minishell(void);
void    init_minishell(char **envp);
void    init_symbols(void);
void    print_dict(t_elems *elem, void *o);
void    destroy_minishell(void);



int				cmp(void *cont1, void *cont2, int size);
void			init_parse(const char *str);

//env
int				cmp_env(void *cont1, void *cont2);
int				comp_var(void *c1, void *c2);
void			create_env(char **envp);
t_env			*create_content(char *total);
char			**env_split(char *str, char sep);
void			del_elem(void *content);

//utils
char			**env_split(char *str, char sep);

//tokens
void			init_tokens(void);
t_token			*c_token(char *s, int type);
void			del_token(void *token);

//states
void			*infile_state(char **s, int add);
void			*var_state(char **s, int add);
char			*aux_state(char **s, char *lex, t_dict *p_sym);
void			*lstr_state(char **s, int add);
void			*str_state(char **s, int add);
void			*non_symbol_state(char **s, int add);
void			*outfile_state(char **s, int add);
int				check_tilde(char **s);
void			*heredoc_state(char **s, int add);

//symbols
int				comp_symbols_search(void *c1, void *c2);
int				comp_symbols_build(void *c1, void *c2);


void			signals_hand(void);
int				cmp_env(void *cont1, void *cont2);

void			export_empty(t_tree *root);
void			delexer(void);

#endif