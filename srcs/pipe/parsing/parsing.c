/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci@student.42lisboa.com <mvenanci    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:15:44 by mvenanci@st       #+#    #+#             */
/*   Updated: 2023/01/20 17:31:39 by mvenanci@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

char	*find_path_var(char **env)
{
	while (*env)
	{
		if (!strings().equal_n(*env, "PATH=", 5))
			return (*env + 5);
		env++;
	}
	return (NULL);
}

void	parse_here_doc(int *fd_in, char *lim, int *flag)
{
	char	*s;

	*fd_in = open("temp", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	lim = strings().join(lim, "", "\n");
	while (strings().equal_n(s, lim, strings().len(lim)))
	{
		s = readline("heredoc>");
		if (!strings().equal_n(s, lim, strings().len(lim)))
			break ;
		write(*fd_in, s, strings().len(s));
		free(s);
	}
	free(lim);
	close(*fd_in);
	*fd_in = open("temp", O_RDONLY);
	*flag += 1;
}

char	*find_cmds(char **paths, char *av)
{
	char	*temp;

	if (!av)
		return (ft_calloc(1));
	while (*paths)
	{
		temp = strings().join(*paths, av, "/");
		if (!access(temp, F_OK))
			return (temp);
		free(temp);
		paths++;
	}
	return (strings().copy(av));
}
