/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:47:55 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/03 15:34:47 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

//int	    cmp(void *cont1, void *cont2, int size)
//{
//	int		i;
//	char	*str1;
//	char	*str2;
//
//	str1 = ((t_env *)cont1)->splitted[0];
//	str2 = (char *)cont2;
//	i = -1;
//	if (str1 && str2)
//		while (++i < size && (str1[i] && str2[i]))
//			if (str1[i] != str2[i])
//				return ((unsigned char )str1[i] - (unsigned char )str2[i]);
//	return (0);
//}

void	export_empty(t_tree *root, int fd)
{
    char *msg;
    char *tmp;

	if (root->left)
		export_empty(root->left, fd);
    tmp = s().join(((t_env *)root->cont)->splitted[0], ((t_env *)root->cont)->splitted[1], "=\"");
    msg = s().join("declare -x ", "\"\n", tmp);
    write(fd, msg, s().len(msg, 0));
    free(msg);
    free(tmp);
	if (root->right)
		export_empty(root->right, fd);
}

void	add_new(char *splitted, char *new)
{
	free(splitted);
	array(m()->env)->add(create_cont(new))->del = del_elem;
}

void	change_var(t_tree *var, char *new, char *splitted)
{
	free(((t_env *)var->cont)->splitted[1]);
	((t_env *)var->cont)->splitted[1] = splitted;
	free(((t_env *)var->cont)->total);
	((t_env *)var->cont)->total = s().copy(new);
}

int	export(void *cont, int fd)
{
	t_tree	*temp;
	char	**splitted;
	char	**vars;
	char	*err;
	int		i;

	i = -1;
	vars = (char **)cont;
	while (vars[++i])
	{
		splitted = env_split(vars[i], '=');
		temp = array(m()->env)->search_tree(NULL, splitted[0]);
		array(m()->env)->cmp = cmp_env;
		if (!s().len(splitted[0], 0) || s().alnum(splitted[0]) || !(__isalpha(splitted[0][0])))
		{
			err = s().join("export: ", ": not a valid identifier\n", vars[i]);
			cona(err);
			free(err);
            free_pp(splitted);
            array(m()->env)->cmp = comp_var;
            return (1);
		}
		else if (!temp)
			add_new(splitted[1], vars[i]);
		else
			change_var(temp, vars[i], splitted[1]);
		free(splitted[0]);
		free(splitted);
		array(m()->env)->cmp = comp_var;
	}
	free(m()->a_env);
	m()->a_env = (char **)array(m()->env)->to_array();
	if (!s().len(vars[0], 0))
		export_empty(array(m()->env)->root, fd);
	return (0);
}
