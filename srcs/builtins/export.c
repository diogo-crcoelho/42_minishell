/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:47:55 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 15:49:05 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	cmp(void *cont1, void *cont2, int size)
{
	int		i;
	char	*str1;
	char	*str2;

	str1 = ((t_env *)cont1)->splitted[0];
	str2 = (char *)cont2;
	i = -1;
	if (str1 && str2)
		while (++i < size && (str1[i] && str2[i]))
			if (str1[i] != str2[i])
				return ((unsigned char )str1[i] - (unsigned char )str2[i]);
	return (0);
}

void	export_empty(t_tree *root)
{
	if (root->left)
		export_empty(root->left);
	printf("declare +x %s\n",((t_env *)root->cont)->total);
	if (root->right)
		export_empty(root->right);
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

int	export(void *cont)
{
	t_tree	*temp;
	char	**splitted;
	int		exit_status;

	exit_status = 1;
	splitted = env_split((char *)cont, '=');
	temp = array(m()->env)->search_tree(NULL, splitted[0]);
	array(m()->env)->cmp = cmp_env;
	if (!cont)
		export_empty(array(m()->env)->root);
	else if (s().alnum(splitted[0]))
		ft_exit(&exit_status);
	else if (!temp)
		add_new(splitted[1], (char *)cont);
	else
		change_var(temp, (char *)cont, splitted[1]);
	free(splitted[0]);
	free (splitted);
	array(m()->env)->cmp = comp_var;
	return (0);
}
