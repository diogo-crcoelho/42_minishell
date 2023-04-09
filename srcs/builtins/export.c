/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:47:55 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/09 18:47:32 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	export_empty(t_tree *root, int fd)
{
	char	*msg;
	char	*tmp;

	if (root->left)
		export_empty(root->left, fd);
	if (((t_env *)root->cont)->splitted[1])
	{
		tmp = s().join(((t_env *)root->cont)->splitted[0], \
						((t_env *)root->cont)->splitted[1], \
						"=\"");
		msg = s().join("declare -x ", "\"\n", tmp);
		free(tmp);
	}
	else
	{
		msg = s().join("declare -x ", "\n", ((t_env *)root->cont)->splitted[0]);
	}
	write(fd, msg, s().len(msg, 0));
	free(msg);
	if (root->right)
		export_empty(root->right, fd);
}

void	add_new(char *splitted, char *new)
{
	free(splitted);
	array(m()->env)->add(create_cont(new))->del = del_elem;
}

void	change_var(t_elems *var, char *new, char *splitted)
{
	free(((t_env *)var->cont)->splitted[1]);
	((t_env *)var->cont)->splitted[1] = splitted;
	free(((t_env *)var->cont)->total);
	((t_env *)var->cont)->total = s().copy(new);
}

int	export_cut_lines(char *vars)
{
	char	**splitted;
	t_elems	*temp;
	char	*err;

	splitted = env_split(vars, '=');
	temp = array(m()->env)->search(comp_var, splitted[0]);
	array(m()->env)->cmp = cmp_env;
	if (!s().len(splitted[0], 0) || s().alnum(splitted[0]) || \
		!(__isalpha(splitted[0][0])))
	{
		err = s().join("export: ", ": not a valid identifier\n", vars);
		cona(err);
		free(err);
		free_pp(splitted);
		array(m()->env)->cmp = comp_var;
		return (1);
	}
	else if (!temp)
		add_new(splitted[1], vars);
	else
		change_var(temp, vars, splitted[1]);
	free(splitted[0]);
	free(splitted);
	array(m()->env)->cmp = comp_var;
	return (0);
}

int	export(void *cont, int fd)
{
	char	**vars;
	int		i;

	i = -1;
	vars = (char **)cont;
	while (vars[++i])
		if (export_cut_lines(vars[i]))
			return (1);
	free(m()->a_env);
	m()->a_env = (char **)array(m()->env)->to_array();
	if (!s().len(vars[0], 0))
		export_empty(array(m()->env)->root, fd);
	return (0);
}
