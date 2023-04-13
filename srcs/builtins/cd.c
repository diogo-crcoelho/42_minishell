/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:00:37 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/04/13 15:26:00 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// Podemos implementar o cd -...
// like guradarmos na estrutura global o caminho atual sempre que chamarmos o cd

void	g_path(char *old)
{
	char	**pwds;
	char	str[PATH_MAX];

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
		err_hand("cd: too many arguments\n", 0);
		return (1);
	}
	path = cd_cut_lines(path);
	err = chdir(path);
	if (!err)
		g_path(old);
	if (err && err++ && ++err)
		err_hand(s().join(path, "No such file or directory\n", ": "), 1);
	if (path)
		free(path);
	return (err);
}
