/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:51:10 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/12 15:14:39 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_isalnum(char c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || (c <= '9'
			&& c >= '0'))
		return (1);
	return (0);
}

char	*aux_state(char **str, char *lex, t_dict *p_sym)
{
	char	*temp;
	char	*temp_symbol;
	t_dict	*symbol;

	symbol = NULL;
	if (array(m()->symbols)->search_tree(array(m()->symbols)->root, *str))
		symbol = (t_dict *)array(m()->symbols) \
			->search_tree(array(m()->symbols)->root, *str)->cont;
	temp = lex;
	if (symbol && p_sym->comp[symbol->value])
	{
		temp_symbol = symbol->state(str, 0);
		(*str)--;
		lex = s().join(lex, temp_symbol, "");
		free(temp_symbol);
	}
	else
		lex = s().append(lex, **str);
	free(temp);
	return (lex);
}

void	*var_state(char **str, int add)
{
	t_dict	*p_sym;
	char	*var;
	char	*temp;

	p_sym = ((t_dict *)array(m()->symbols)->search_tree(NULL, *str)->cont);
	temp = *str + 1;
	(*str)++;
	if (**str == '?' && (*str)++)
		var = ft_itoa(m()->exit_status);
	else if (!check_var_validity(**str) || (**str == '"' && m()->in_quotes))
		var = s().copy("$");
	else if (**str && ft_isalnum(**str))
		var = var_state_cut_lines(str, temp);
	else
		var = ft_calloc(2);
	if (add)
		(array(m()->tokens))->add(c_token(var, p_sym->value))->del = del_token;
	return (var);
}

void	*infile_state(char **str, int add)
{
	t_dict	*p_sym;
	char	*infile;

	(void)add;
	p_sym = ((t_dict *)array(m()->symbols) \
		->search_tree(array(m()->symbols)->root, *str)->cont);
	infile = ft_calloc(2);
	(*str)++;
	if (p_sym->value == HERE || p_sym->value == APP)
		(*str)++;
	while (**str && **str == ' ')
		(*str)++;
	while (**str && **str != ' ' && **str != '|' && **str != '<'
		&& **str != '>')
	{
		infile = aux_state(str, infile, p_sym);
		if (!**str)
			break ;
		(*str)++;
	}
	(array(m()->tokens))->add(c_token(infile, p_sym->value))->del = del_token;
	return (infile);
}

void	*str_state(char **str, int add)
{
	t_dict	*p_sym;
	char	*infile;

	(void)add;
	p_sym = ((t_dict *)array(m()->symbols) \
		->search_tree(NULL, *str)->cont);
	infile = ft_calloc(2);
	(*str)++;
    m()->in_quotes = 1;
    while (**str && **str != '"')
	{
		infile = aux_state(str, infile, p_sym);
		if (!**str)
			break ;
		(*str)++;
	}
    m()->in_quotes = 0;
	if (**str)
		(*str)++;
	if (add)
		(array(m()->tokens))->add(c_token(infile,
					p_sym->value))->del = del_token;
	return (infile);
}
