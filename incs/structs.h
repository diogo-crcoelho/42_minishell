//
// Created by mvenanci on 2/13/23.
//

#ifndef INC_42_MINISHELL_STRUCTS_H
#define INC_42_MINISHELL_STRUCTS_H

typedef struct s_prompt t_prompt;
typedef struct s_token t_token;
typedef struct s_mini t_mini;
typedef struct s_dict t_dict;
typedef struct s_cmd t_cmd;
typedef struct s_env t_env;

enum e_type{
    VAR,
    IN,
    OUT,
    STR,
    LSTR,
    HERE
};

struct s_mini{
	void	*env;
	void	*cmds;
	int 	exit_status;
	char 	*prev_path;
    void    *tokens;
    void    *symbols;
};

struct s_env{
	char	*total;
	char	**splitted;
};

struct s_dict{
    char    *key;
    int     value;
    void    *(*state)(char **str, int add);
};

struct s_token{
    char    *token;
    int     type;
};

struct s_cmd{
	char	*path;
	char	**args;
	int		fd[2];
    int     fd_red[2];
	int		pid;
};


#endif //INC_42_MINISHELL_STRUCTS_H
