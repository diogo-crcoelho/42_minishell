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

//int **compatibility(void)
//{
//
//}

char    *aux_state(char **s, char *lex, t_dict *p_sym)
{
    char    *temp;
    char    *temp_symbol;
    t_dict  *symbol;

    symbol = NULL;
    if (array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root, *s))
        symbol = (t_dict *)array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root, *s)->content;
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

void    *var_state(char **s, int add)
{
    t_dict  *p_sym;
    char    *variable;
    char    *temp;

    p_sym = ((t_dict *)array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root, *s)->content);
    temp = *s + 1;
    (*s)++;
    while (**s && ft_isalnum(**s))
        (*s)++;
    temp = strings().copy_n(temp, *s - temp);
    if (array(minishell()->env)->search_tree(array(minishell()->env)->root, temp))
        variable = strings().copy(((t_env *)array(minishell()->env)->search_tree(array(minishell()->env)->root, temp)->content)->splitted[1]);
    else
        variable = ft_calloc(1);
    if (add)
        array(minishell()->tokens)->add(c_token(variable, p_sym->value));
    free(temp);
    return (variable);
}

void    *infile_state(char **s, int add)
{
    t_dict  *p_sym;
    char    *infile;

    (void)add;
    p_sym = ((t_dict *)array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root, *s)->content);
    infile = ft_calloc(1);
    (*s)++;
    while (**s && **s == ' ')
        (*s)++;
    while (**s && **s != ' ')
    {
        infile = aux_state(s, infile, p_sym);
        if (!**s)
            break ;
        (*s)++;
    }
    array(minishell()->tokens)->add(c_token(infile, p_sym->value));
    return (infile);
}

void    *str_state(char **s, int add)
{
    t_dict  *p_sym;
    char    *infile;

    (void)add;
    p_sym = ((t_dict *)array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root, *s)->content);
    infile = ft_calloc(1);
    (*s)++;
    while (**s && **s != '"')
    {
        infile = aux_state(s, infile, p_sym);
        if (!**s)
            break ;
        (*s)++;
    }
    if (add)
        array(minishell()->tokens)->add(c_token(infile, p_sym->value));
    return (infile);
}

void    *lstr_state(char **s, int add)
{
    int     type;
    char    *lstr;
    char    *temp;

    type = ((t_dict *)array(minishell()->symbols)->search_tree(array(minishell()->symbols)->root, *s)->content)->value;
    (*s)++;
    temp = *s;
    while (**s && **s != 39)
        (*s)++;
    lstr = strings().copy_n(temp, *s - temp);
    (*s)++;
    if (add)
        array(minishell()->tokens)->add(c_token(lstr, type));
    return (lstr);
}