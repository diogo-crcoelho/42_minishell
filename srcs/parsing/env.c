//
// Created by miguel on 20-02-2023.
//

#include "../../incs/minishell.h"

int comp_var(void *c1, void *c2)
{
    char    *in_tree;
    char    *out_tree;

    in_tree = ((t_env *)c1)->splitted[0];
    out_tree = c2;
    return (strings().equal(in_tree, out_tree));
}
