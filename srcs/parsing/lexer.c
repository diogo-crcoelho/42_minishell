//
// Created by miguel on 17-02-2023.
//

#include "../../incs/minishell.h"

int	ft_isalnum(char c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || (c <= '9'
			&& c >= '0'))
		return (1);
	return (0);
}

char	*aux_state(char **s, char *lex, t_dict *p_sym)
{
	char	*temp;
	char	*temp_symbol;
	t_dict	*symbol;

	symbol = NULL;
	if (array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root,
			*s))
		symbol = (t_dict *)array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root,
				*s)->content;
	temp = lex;
	if (symbol && p_sym->comp[symbol->value])
	{
		temp_symbol = symbol->state(s, 0);
		(*s)--;
		lex = strings().join(lex, temp_symbol, "");
		free(temp_symbol);
	}
	else
		lex = strings().append(lex, **s);
	free(temp);
	return (lex);
}

void	*var_state(char **s, int add)
{
	t_dict	*p_sym;
	char	*variable;
	char	*temp;

	p_sym = ((t_dict *)array(minishell()->symbols)->search_tree(NULL,
				*s)->content);
	temp = *s + 1;
	(*s)++;
	while (**s && ft_isalnum(**s))
		(*s)++;
	temp = strings().copy_n(temp, *s - temp);
	if (array(minishell()->env)->search_tree(NULL, temp))
		variable = strings().copy(((t_env *)array(minishell()->env)->search_tree(array(minishell()->env)->root,
						temp)->content)->splitted[1]);
	else
		variable = ft_calloc(1);
	if (add)
		array(minishell()->tokens)->add(c_token(variable,
					p_sym->value))->del = del_token;
	free(temp);
	return (variable);
}

void	*infile_state(char **s, int add)
{
	t_dict	*p_sym;
	char	*infile;

	(void)add;
	p_sym = ((t_dict *)array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root,
				*s)->content);
	infile = ft_calloc(1);
	(*s)++;
	if (p_sym->value == HERE || p_sym->value == APP)
		(*s)++;
	while (**s && **s == ' ')
		(*s)++;
	while (**s && **s != ' ' && **s != '|')
	{
		infile = aux_state(s, infile, p_sym);
		if (!**s)
			break ;
		(*s)++;
	}
	array(minishell()->tokens)->add(c_token(infile,
				p_sym->value))->del = del_token;
	return (infile);
}

void	*str_state(char **s, int add)
{
	t_dict	*p_sym;
	char	*infile;

	(void)add;
	p_sym = ((t_dict *)array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root,
				*s)->content);
	infile = ft_calloc(1);
	(*s)++;
	while (**s && **s != '"')
	{
		infile = aux_state(s, infile, p_sym);
		if (!**s)
			break ;
		(*s)++;
	}
	if (**s)
		(*s)++;
	if (add)
		array(minishell()->tokens)->add(c_token(infile,
					p_sym->value))->del = del_token;
	return (infile);
}

void	*lstr_state(char **s, int add)
{
	int		type;
	char	*lstr;
	char	*temp;

	type = ((t_dict *)array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root,
				*s)->content)->value;
	(*s)++;
	temp = *s;
	while (**s && **s != 39)
		(*s)++;
	lstr = strings().copy_n(temp, *s - temp);
	if (**s)
		(*s)++;
	if (add)
		array(minishell()->tokens)->add(c_token(lstr, type))->del = del_token;
	return (lstr);
}

void	*non_symbol_state(char **s, int add)
{
	char	*temp;
	char	*temp_free;
	t_dict	*symbol;

	temp = ft_calloc(1);
	while (**s && **s != ' ' && **s != '|')
	{
		symbol = (t_dict *)array(minishell()->symbols)->search_tree(NULL, *s);
		temp_free = temp;
		if (symbol)
		{
			symbol = ((t_tree *)(symbol))->content;
			temp = strings().join(temp, symbol->state(s, 0), "");
			continue ;
		}
		else
			temp = strings().append(temp, **s);
		free(temp_free);
		if (!**s)
			break ;
		(*s)++;
	}
	if (add)
		array(minishell()->tokens)->add(c_token(temp, CMD))->del = del_token;
	return (temp);
}

int	check_validity(char *s)
{
	if (*s == '~' && (*(s + 1) == ' ' || *(s + 1) == '|' || *(s + 1) == '/'
			|| !*(s + 1)))
		return (1);
	return (0);
}

int	check_tilde(char **s)
{
	char	*tilde;
	t_token	*token;

	tilde = ((t_env *)array(minishell()->env)->search_tree(0,
				"HOME")->content)->splitted[1];
	token = (t_token *)array(minishell()->tokens)->end;
	if (!token && check_validity(*s))
	{
		array(minishell()->tokens)->add(c_token(strings().copy(tilde), VAR));
		(*s)++;
		return (1);
	}
	else if (!check_validity(*s))
		return (0);
	else if (token)
		token = ((t_elems *)token)->content;
	if ((token->type == SPC || token->type == PIPE) && check_validity(*s))
	{
		array(minishell()->tokens)->add(c_token(strings().copy(tilde),
					VAR))->del = del_token;
		(*s)++;
		return (1);
	}
	return (0);
}

void	*heredoc_state(char **s, int add)
{
	char *here;

	*s += 2;
	while (**s == ' ' || **s == '\t')
		(*s)++;
	here = *s;
	while (**s && **s != ' ' && **s == '\t' && **s != '|')
		(*s)++;
	here = strings().copy_n(here, *s - here);
	if (add)
		array(minishell()->tokens)->add(c_token(here, HERE))->del = del_token;
	return (here);
}