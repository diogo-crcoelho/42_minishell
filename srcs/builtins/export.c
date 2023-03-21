
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

void export(char *var)
{
    t_elems *temp;
    char    **splitted;

    splitted = env_split(var, '=');
    temp = array(minishell()->env)->search(cmp, splitted[0], strings().len(var, 0));
    array(minishell()->env)->cmp = cmp_env;
    if (!var)
    {
        export_empty(array(minishell()->env)->root);
        return;
    }
    if (strings().alnum(splitted[0]))
        ft_exit(1);
    if (!temp)
    {
        free(splitted[1]);
        array(minishell()->env)->add(create_content(var))->del = del_elem;
    }
    else
    {
        free(((t_env *)temp->content)->splitted[1]);
        ((t_env *)temp->content)->splitted[1] = splitted[1];
        free(((t_env *)temp->content)->total);
        ((t_env *)temp->content)->total = strings().copy(var);
    }
    free(splitted[0]);
    free (splitted);
    array(minishell()->env)->cmp = comp_var;
}