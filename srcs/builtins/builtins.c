//
// Created by miguel on 26-03-2023.
//

#include "../../incs/minishell.h"

void    del_builtin(void *builtin)
{
    free(((t_built *)builtin)->key);
    free(builtin);
}

t_built *c_builtin(char *key)
{
    t_built *new;

    new = ft_calloc(sizeof(t_built));
    new->key = key;
    return (new);
}

void    init_builtins(void)
{
    minishell()->builtins = creat_array();
    array(minishell()->builtins)->cmp = comp_symbols_build;
    ((t_built *)array(minishell()->builtins)->add(c_builtin(strings().copy("pwd")))->content)->builtin = pwd;
    array(minishell()->builtins)->end->del = del_builtin;
    ((t_built *)array(minishell()->builtins)->add(c_builtin(strings().copy("env")))->content)->builtin = env;
    array(minishell()->builtins)->end->del = del_builtin;
    ((t_built *)array(minishell()->builtins)->add(c_builtin(strings().copy("unset")))->content)->builtin = unset;
    array(minishell()->builtins)->end->del = del_builtin;
    ((t_built *)array(minishell()->builtins)->add(c_builtin(strings().copy("export")))->content)->builtin = export;
    array(minishell()->builtins)->end->del = del_builtin;
    ((t_built *)array(minishell()->builtins)->add(c_builtin(strings().copy("cd")))->content)->builtin = cd;
    array(minishell()->builtins)->end->del = del_builtin;
    ((t_built *)array(minishell()->builtins)->add(c_builtin(strings().copy("echo")))->content)->builtin = echo;
    array(minishell()->builtins)->end->del = del_builtin;
    ((t_built *)array(minishell()->builtins)->add(c_builtin(strings().copy("exit")))->content)->builtin = ft_exit;
    array(minishell()->builtins)->end->del = del_builtin;
}
