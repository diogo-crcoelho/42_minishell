/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:54:47 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 15:55:26 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	*lstr_state(char **str, int add)
{
	int		type;
	char	*lstr;
	char	*temp;

	type = ((t_dict *)array(m()->symbols)->\
		search_tree(array(m()->symbols)->root, *str)->cont)->value;
	(*str)++;
	temp = *str;
	while (**str && **str != 39)
		(*str)++;
	lstr = s().copy_n(temp, *str - temp);
	if (**str)
		(*str)++;
	if (add)
		(array(m()->tokens))->add(c_token(lstr, type))->del = del_token;
	return (lstr);
}

void	*non_symbol_state(char **str, int add)
{
	char	*temp;
	char	*temp_free;
	t_dict	*symbol;

	temp = ft_calloc(1);
	while (**str && **str != ' ' && **str != '|')
	{
		symbol = (t_dict *)array(m()->symbols)->search_tree(NULL, *str);
		temp_free = temp;
		if (symbol)
		{
			symbol = ((t_tree *)(symbol))->cont;
			temp = s().join(temp, symbol->state(str, 0), "");
			continue ;
		}
		else
			temp = s().append(temp, **str);
		free(temp_free);
		if (!**str)
			break ;
		(*str)++;
	}
	if (add)
		(array(m()->tokens))->add(c_token(temp, CMD))->del = del_token;
	return (temp);
}

int	check_validity(char *str)
{
	if (*str == '~' && (*(str + 1) == ' ' || *(str + 1) == '|' || *(str + 1) == '/'
			|| !*(str + 1)))
		return (1);
	return (0);
}

int	check_tilde(char **str)
{
	char	*tilde;
	t_token	*token;

	tilde = ((t_env *)array(m()->env)->\
		search_tree(0, "HOME")->cont)->splitted[1];
	token = (t_token *)array(m()->tokens)->end;
	if (!token && check_validity(*str))
	{
		(array(m()->tokens))->add(c_token(s().copy(tilde), VAR));
		(*str)++;
		return (1);
	}
	else if (!check_validity(*str))
		return (0);
	else if (token)
		token = ((t_elems *)token)->cont;
	if ((token->type == SPC || token->type == PIPE) && check_validity(*str))
	{
		(array(m()->tokens))->add(c_token(s().copy(tilde), VAR))->\
			del = del_token;
		(*str)++;
		return (1);
	}
	return (0);
}

void	*heredoc_state(char **str, int add)
{
	char	*here;

	*str += 2;
	while (**str == ' ' || **str == '\t')
		(*str)++;
	here = *str;
	while (**str && **str != ' ' && **str != '\t' && **str != '|')
		(*str)++;
	here = s().copy_n(here, (*str - here));
	if (add)
		(array(m()->tokens))->add(c_token(here, HERE))->del = del_token;
	return (here);
}
