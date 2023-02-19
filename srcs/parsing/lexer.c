//
// Created by miguel on 17-02-2023.
//

#include "../../incs/minishell.h"

int ft_isalnum(char c)
{
    if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || (c <= '9' && c >= '0'))
        return (1);
    return (0);
}

char    *aux_state(char **s, char *lex)
{
    char    *temp;
    char    *temp_symbol;
    t_dict  *symbol;

    symbol = NULL;
    if (array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root, *s, comp_symbols_search))
        symbol = (t_dict *)array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root, *s, comp_symbols_search)->content;
    temp = lex;
    if (symbol)
    {
        temp_symbol = symbol->state(s, 0);
        lex = strings().join(lex, temp_symbol, "");
        free(temp_symbol);
    }
    else
        lex = strings().append(lex, **s);
    free(temp);
    return (lex);
}

void    *var_state(char **s, int add)
{
    int     type;
    char    *variable;
    char    *temp;

    type = ((t_dict *)array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root, *s, comp_symbols_search)->content)->value;
    temp = *s + 1;
    while (**s && ft_isalnum(**s))
        (*s)++;
    temp = strings().copy_n(temp, *s - temp);
    if (array(minishell()->env)->search_tree(array(minishell()->env)->root, temp, comp_symbols_search))
        variable = strings().copy(((t_env *)array(minishell()->env)->search_tree(array(minishell()->env)->root, temp, comp_symbols_search)->content)->splitted[1]);
    else
        variable = ft_calloc(1);
    if (add)
        array(minishell()->tokens)->add(c_token(variable, type));
    free(temp);
    return (variable);
}

void    *infile_state(char **s, int add)
{
    int     type;
    char    *infile;

    (void)add;
    type = ((t_dict *)array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root, *s, comp_symbols_search)->content)->value;
    infile = ft_calloc(1);
    while (**s && **s == ' ')
        (*s)++;
    while (**s && **s != ' ')
    {
        infile = aux_state(s, infile);
        (*s)++;
    }
    array(minishell()->tokens)->add(c_token(infile, type));
    return (infile);
}

