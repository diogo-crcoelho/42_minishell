/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:59:42 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/15 15:59:48 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <termios.h>

typedef struct s_prompt	t_prompt;
typedef struct s_token	t_token;
typedef struct s_built	t_built;
typedef struct s_mini	t_mini;
typedef struct s_dict	t_dict;
typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;

enum					e_type
{
	VAR,
	IN,
	OUT,
	APP,
	STR,
	LSTR,
	HERE,
	CMD,
	PIPE,
	SPC,
	BLTIN
};

struct					s_mini
{
	void				*env;
	char				**a_env;
	void				*cmds;
	int					inter;
	int					exit_status;
	void				*tokens;
	void				*symbols;
	void				*b;
	char				*home;
	int					c_count;
	volatile int		h;
	char				*tmp;
	struct termios		term;
	int					in_quotes;
};

struct					s_env
{
	char				*total;
	char				**splitted;
};

struct					s_dict
{
	char				*key;
	int					value;
	int					*comp;
	void				*(*state)(char **str, int add);
};

struct					s_built
{
	char				*key;
	int					(*b)(void *, int);
};

struct					s_token
{
	char				*token;
	int					type;
};

struct					s_cmd
{
	char				*path;
	char				**args;
	int					fd[2];
	int					fd_red[2];
	char				*infile;
	char				*outfile;
	int					app;
	int					pid;
	int					err;
	int					ord;
};

#endif //INC_42_m_STRUCTS_H
