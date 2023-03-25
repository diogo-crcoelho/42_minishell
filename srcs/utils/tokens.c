//
// Created by miguel on 19-02-2023.
//

#include "../../incs/minishell.h"

void    del_token(void *token)
{
    free(((t_token *)token)->token);
    free(token);
}

t_token *c_token(char *s, int type)
{
    t_token *new;

    new = ft_calloc(sizeof(t_token));
    new->token = s;
    new->type = type;
    return (new);
}

int comp_token(void *c1, void *c2)
{
    char    *in_tree;
    char    *out_tree;

    in_tree = ((t_token *)c1)->token;
    out_tree = (char *)c2;
    return (strings().equal(in_tree, out_tree));
}

void    init_tokens(void)
{
    minishell()->tokens = creat_array();
    array(minishell()->tokens)->build_tree();
    array(minishell()->tokens)->cmp = comp_token;
}
