/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:00:37 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/04/08 17:00:41 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// Podemos implementar o cd -...
// like guradarmos na estrutura global o caminho atual sempre que chamarmos o cd

void	g_path(char *old)
{
	t_tree	*tt;
	char	**pwds;
	char	str[PATH_MAX];

	tt = array(m()->env)->search_tree(NULL, "OLDPWD");
	free(m()->prev_path);
	m()->prev_path = s().copy(((t_env *)tt->cont)->splitted[1]);
	pwds = ft_calloc((sizeof(char *) * 3));
	pwds[0] = s().join("OLDPWD=", old, "");
	pwds[1] = s().join("PWD=", getcwd(str, PATH_MAX), "");
	export(pwds, 0);
	free_pp(pwds);
	free(old);
}

char	*cd_cut_lines(char *path)
{
	if (!s().len(path, 0))
		path = s().copy(m()->home);
	else if (!s().equal(path, "-"))
		path = s().copy(m()->prev_path);
	else
		path = s().copy(path);
	return (path);
}

int	cd(void *cont, int fd)
{
	int		err;
	char	*path;
	char	*old;

	(void)fd;
	path = ((char **)cont)[0];
	old = NULL;
	old = getcwd(old, PATH_MAX);
	if (path && ((char **)cont)[1])
	{
		cona("cd: too many arguments\n");
		return (1);
	}
	path = cd_cut_lines(path);
	err = chdir(path);
	if (!err)
		g_path(old);
	if (path)
		free(path);
	if (err && err++ && ++err)
		cona(" No such file or directory\n");
	return (err);
}
