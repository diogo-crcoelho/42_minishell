/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:31:16 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/26 16:56:29 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		add_space(char *s);

void	lex(char **temp)
{
	t_dict	*symbol;

	while (**temp)
	{
		symbol = (t_dict *)array(m()->symbols)->search_tree(NULL, *temp);
		if (check_tilde(temp))
			continue ;
		if (symbol)
		{
			symbol = ((t_tree *)symbol)->cont;
			symbol->state(temp, 1);
			continue ;
		}
		else if (**temp && **temp != ' ' && **temp != '|')
			non_symbol_state(temp, 1);
		while (**temp == ' ' || (add_space(*temp)
				&& !array(m()->tokens)->add(c_token(" ", SPC))))
			(*temp)++;
		if (**temp == '|' && array(m()->tokens)->add(c_token("|", PIPE)))
			(*temp)++;
	}
}

void	destroy_m(void)
{
	free(m()->a_env);
	array(m()->tokens)->destroy();
	array(m()->cmds)->destroy();
	array(m()->symbols)->destroy();
	array(m()->env)->destroy();
	array(m()->b)->destroy();
	free(m()->home);
}

void	reload(void)
{
	t_elems	*elem;

	elem = array(m()->cmds)->begin;
	while (elem)
	{
		if (((t_cmd *)elem->cont)->fd_red[1] > 2)
			close(((t_cmd *)elem->cont)->fd_red[1]);
		if (((t_cmd *)elem->cont)->fd_red[0] > 2)
			close(((t_cmd *)elem->cont)->fd[0]);
		if (((t_cmd *)elem->cont)->fd[1] > 2)
			close(((t_cmd *)elem->cont)->fd[1]);
		if (((t_cmd *)elem->cont)->fd[0] > 2)
			close(((t_cmd *)elem->cont)->fd[0]);
		elem = elem->next;
	}
	array(m()->tokens)->destroy();
	m()->tokens = creat_array();
	array(m()->cmds)->destroy();
	m()->cmds = creat_array();
	m()->h = 0;
	m()->inter = 0;
}

void print_tokens(t_elems *elem, void *o)
{
    (void)o;
    t_token *token = elem->cont;
    printf("=================================\n");
    printf("token -- '%s'\n", token->token);
    printf("type -- %d\n", token->type);
    printf("=================================\n");
}

void	new_func(void)
{
	char	*str;
	char	*temp;

	while (1)
	{
		signals_hand();
		str = readline("not bash> ");
		if (!str)
		{
			m()->exit_status = 0;
			break ;
		}
		temp = str;
		lex(&temp);
		delexer(array(m()->tokens)->begin, 0);
//        array(m()->tokens)->for_each(print_tokens, NULL);
		history(array(m()->cmds)->begin, str);
		if (130 != m()->h )
			pipex();
		reload();
		free(str);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		exit(1);
	(void)argv;
	(void)envp;
	init_m(envp);
	new_func();
	s_exit(m()->exit_status);
}
