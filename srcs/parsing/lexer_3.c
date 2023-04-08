/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:18:51 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/08 17:01:03 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	check_tilde(char **str)
{
	char	*tilde;
	t_token	*token;

	update_home();
	tilde = m()->home;
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
		(array(m()->tokens))->add(c_token(s().copy(tilde),
					VAR))->del = del_token;
		(*str)++;
		return (1);
	}
	return (0);
}

void	*heredoc_state(char **str, int add)
{
	char *here;

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