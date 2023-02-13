//
// Created by mvenanci on 2/13/23.
//

#ifndef INC_42_MINISHELL_STRUCTS_H
#define INC_42_MINISHELL_STRUCTS_H

typedef struct s_prompt t_prompt;
typedef struct s_mini t_mini;
typedef struct s_cmd t_cmd;
typedef struct s_env t_env;

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


#endif //INC_42_MINISHELL_STRUCTS_H
