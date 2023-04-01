/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:41:56 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/27 15:57:57 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../srcs/libs/list/list_utils.h"
# include "../srcs/libs/strs/ft_strings.h"
# include "structs.h"
# include "pipex.h"


typedef 	void	(*t_func)();
//t_func func = (void *) printf;

//general
unsigned long hash(char *str);

//b
void    init_b(void);
int     pwd(void* cont);
int     env(void* cont);
int     unset(void *cont);
int     export(void* cont);
int     cd(void *path);
int 	echo(void *cont);
int	    ft_exit(void* cont);
int		built(t_elems *elem);
void	destroy_cmds(t_elems *elem);

t_mini 	*m(void);
void    init_m(char **envp);
void    init_symbols(void);
void    print_dict(t_elems *elem, void *o);
void    destroy_m(void);



int				cmp(void *cont1, void *cont2, int size);
void			init_parse(const char *str);
void            cona(char *err);
void			free_pp(void *pp);


//env
int				cmp_env(void *cont1, void *cont2);
int				comp_var(void *c1, void *c2);
void			create_env(char **envp);
t_env			*create_cont(char *total);
char			**env_split(char *str, char sep);
void			del_elem(void *cont);

//utils
char			**env_split(char *str, char sep);
char	        *ft_itoa(int n);

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
void			init_symbols(void);
int				*init_comp(int type);
int				comp_symbols_search(void *c1, void *c2);
int				comp_symbols_build(void *c1, void *c2);

void			signals_hand(void);
int				cmp_env(void *cont1, void *cont2);

void			export_empty(t_tree *root);
void			delexer(void);
int	__isalpha(int c);
int s_exit(int sc);


//pipex
int	treat_files(t_cmd *cmd);

#endif