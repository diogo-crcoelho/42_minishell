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

# include "../srcs/libs/list/list_utils.h"
# include "../srcs/libs/strs/ft_strings.h"
# include "pipex.h"
# include "structs.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <wait.h>

//typedef void	(*t_func)();
//t_func func = (void *) printf;

//general
unsigned long	hash(char *str);
void			init_parse(const char *str);
void			cona(char *err);
void			free_pp(void *pp);

//builtins
void			init_b(void);
int				pwd(void *cont, int fd);
int				env(void *cont, int fd);
int				unset(void *cont, int fd);
int				export(void *cont, int fd);
int				cd(void *path, int fd);
int				echo(void *cont, int fd);
int				ft_exit(void *cont, int fd);
int				built(t_elems *elem);
void			destroy_cmds(t_elems *elem);
void			export_empty(t_tree *root, int fd);
int				ft_isalnum(char c);

t_mini			*m(void);
void			init_m(char **envp);
void			init_symbols(void);
void			print_dict(t_elems *elem, void *o);
void			destroy_m(void);
int				cmp(void *cont1, void *cont2, int size);

//env
int				cmp_env(void *cont1, void *cont2);
int				comp_var(void *c1, void *c2);
void			create_env(char **envp);
t_env			*create_cont(char *total);
char			**env_split(char *str, char sep);
void			del_elem(void *cont);
void			shell_lvl(void);
//utils
char			**env_split(char *str, char sep);
char			*ft_itoa(int n);
long			s_atoi(char *str);

//tokens
void			init_tokens(void);
t_token			*c_token(char *s, int type);
int				check_var_validity(char c);
void			del_token(void *token);

//states
char			*var_state_cut_lines(char **str, char *temp);
void			*infile_state(char **s, int add);
void			*var_state(char **s, int add);
char			*aux_state(char **s, char *lex, t_dict *p_sym);
void			*lstr_state(char **s, int add);
void			*str_state(char **s, int add);
void			*non_symbol_state(char **s, int add);
void			*outfile_state(char **s, int add);
int				check_tilde(char **s);
void			*heredoc_state(char **s, int add);
int				check_validity(char *str);
void			update_home(void);

//symbols
int				comp_symbols_search(void *c1, void *c2);
int				comp_symbols_build(void *c1, void *c2);
void			init_symbols(void);
int				*init_comp(int type);
int				comp_symbols_search(void *c1, void *c2);
int				comp_symbols_build(void *c1, void *c2);

void			signals_hand(void);
void			term_change(void);
int				cmp_env(void *cont1, void *cont2);
void			delexer(t_elems *tmp, int flag);
int				__isalpha(int c);
int				__isdigit(int c);
int				s_exit(int sc);

//pipex
void			pipex(void);
int				treat_files(t_cmd *cmd);
void			built_cut_lines(t_cmd *cmd, t_elems *elem);
void			befor_exit(t_cmd *cmd);
void			parse_paths(t_cmd *cmd);
void			**to_array_mini(void);
void			close_pipes(t_cmd *cmd);
#endif