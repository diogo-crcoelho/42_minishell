//
// Created by miguel on 19-02-2023.
//

#include "../../incs/minishell.h"

int     comp_symbols_build(void *c1, void *c2)
{
    char    *in_tree;
    char    *out_tree;

    in_tree = ((t_dict *)c1)->key;
    out_tree = ((t_dict *)c2)->key;
    printf("in_tree: %s out_tree: %s, %i\n", in_tree, out_tree, strings().equal_n(in_tree, out_tree, 2));
    return (strings().equal_n(in_tree, out_tree, 2));
}

int     comp_symbols_search(void *c1, void *c2)
{
    char    *in_tree;
    char    *out_tree;

    in_tree = ((t_dict *)c1)->key;
    out_tree = c2;
    printf("in_tree: %s out_tree: %s, %i\n", in_tree, out_tree, strings().equal_n(in_tree, out_tree, strings().len(in_tree, 0)));
    return (strings().equal_n(in_tree, out_tree, strings().len(in_tree, 0)));
}

void    print_dict(t_elems *elem, void *o)
{
    (void)o;
    t_dict *cont;

    cont = (t_dict *)elem->content;
    printf("\n%s--%d\n", cont->key, cont->value);
}

t_dict  *c_dict(char *key, int value)
{
    t_dict  *new;

    new = ft_calloc(sizeof(t_dict));
    new->key = key;
    new->value = value;
    return (new);
}

void    init_symbols(void)
{
    char    *key;

    key = ft_calloc(3);
    key[0] = '$';
    minishell()->symbols = creat_array();
    array(minishell()->symbols)->cmp = comp_symbols_build;
    ((t_dict *)(array(minishell()->symbols)->add(c_dict(strings().copy(key), VAR))->content))->state = var_state;
    key[0] = '<';
    ((t_dict *)(array(minishell()->symbols)->add(c_dict(strings().copy(key), IN))->content))->state = infile_state;
    key[0] = '>';
    ((t_dict *)(array(minishell()->symbols)->add(c_dict(strings().copy(key), OUT))->content))->state = var_state;
    key[0] = '"';
    ((t_dict *)(array(minishell()->symbols)->add(c_dict(strings().copy(key), STR))->content))->state = var_state;
    key[0] = 39;
    ((t_dict *)(array(minishell()->symbols)->add(c_dict(strings().copy(key), LSTR))->content))->state = var_state;
    key[0] = '<';
    key[1] = '<';
    ((t_dict *)(array(minishell()->symbols)->add(c_dict(strings().copy(key), HERE))->content))->state = var_state;
    array(minishell()->symbols)->build_tree();
    free(key);
}