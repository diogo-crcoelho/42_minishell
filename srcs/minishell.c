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

//TODO

void	pipex(void);

void	print_cmds(void);

t_mini	*m(void)
{
	static t_mini	a;

	return (&a);
}

void	print_tokens(void)
{
	t_elems	*c;
	int		i;

	i = 0;
	c = (array(m()->tokens)->begin);
	while (c)
	{
		printf("Token %d: %s, type=%d\n", i, ((t_token *)(c->cont))->token, \
			((t_token *)(c->cont))->type);
		c = c->next;
		i++;
	}
}

int	add_space(char *s)
{
	if (*s == '|' || !*s)
		return (0);
	else if (((t_token *)array(m()->tokens)->end->cont)->type == PIPE)
		return (0);
	return (1);
}

void	lex(char **temp)
{
	t_dict	*symbol;

	while (**temp)
	{
		symbol = (t_dict *)array(m()->symbols)->search_tree(NULL,
				*temp);
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
		if (**temp == '|' && array(m()->tokens)->add(c_token("|",
					PIPE)))
			(*temp)++;
	}
}

void	destroy_m(void)
{
	array(m()->tokens)->destroy();
	array(m()->cmds)->destroy();
	array(m()->symbols)->destroy();
	array(m()->env)->destroy();
	array(m()->b)->destroy();
	free(m()->prev_path);
	free(m()->a_env);
}

void	reload(void)
{
	array(m()->tokens)->destroy();
	m()->tokens = creat_array();
	array(m()->cmds)->destroy();
	m()->cmds = creat_array();
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	*temp;

	if (argc != 1)
		exit(1);
	(void)argv;
	(void)envp;
	init_m(envp);
	while (1)
	{
		signals_hand();
		str = readline("not bash> ");
		if (!str)
			break ;
		add_history(str);
		temp = str;
		lex(&temp);
//        print_tokens();
		delexer();
//       print_cmds();
		pipex();
		reload();
		free(str);
	}
	destroy_m();
}
