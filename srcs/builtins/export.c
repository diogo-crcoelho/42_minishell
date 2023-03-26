
#include "../../incs/minishell.h"

//falta verificar se o bicho existe

int cmp(void *cont1, void *cont2, int size)
{
    int	i;
    char *str1;
    char *str2;

    str1 = ((t_env *)cont1)->splitted[0];
    str2 = (char *)cont2;
    i = -1;
    if (str1 && str2)
        while (++i < size && (str1[i] && str2[i]))
            if (str1[i] != str2[i])
            {
//                printf("%s--%s\n", str1, str2);
                return ((unsigned char )str1[i] - (unsigned char )str2[i]);
            }
    printf("==========================================\n");
    return (0);
}

void export_empty(t_tree *root)
{
    if (root->left)
        export_empty(root->left);
    printf("declare +x %s\n",((t_env *)root->content)->total);
    if (root->right)
        export_empty(root->right);
}

void    add_new(char *splitted, char *new)
{
    free(splitted);
    array(minishell()->env)->add(create_content(new))->del = del_elem;
}

void    change_var(t_tree *var, char *new, char *splitted)
{
    free(((t_env *)var->content)->splitted[1]);
    ((t_env *)var->content)->splitted[1] = splitted;
    free(((t_env *)var->content)->total);
    ((t_env *)var->content)->total = strings().copy(new);
}

int    export(void* content)
{
    t_tree *temp;
    char    **splitted;
    int     exit_status;

    exit_status = 1;
    splitted = env_split((char *)content, '=');
    temp = array(minishell()->env)->search_tree(NULL, splitted[0]);
    array(minishell()->env)->cmp = cmp_env;
    if (!content)
        export_empty(array(minishell()->env)->root);
    else if (strings().alnum(splitted[0]))
        ft_exit(&exit_status);
    else if (!temp)
        add_new(splitted[1], (char *)content);
    else
        change_var(temp, (char *)content, splitted[1]);
    free(splitted[0]);
    free (splitted);
    array(minishell()->env)->cmp = comp_var;
}