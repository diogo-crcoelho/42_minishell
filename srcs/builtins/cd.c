/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:00:37 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/03/27 15:46:04 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// Podemos implementar o cd -...
// like guradarmos na estrutura global o caminho atual sempre que chamarmos o cd

int	cd(void *cont)
{
	int		err;
	char	*path;

	path = (char *)cont;
	if (!s().len(path, 0))
		path = s().copy(getenv("HOME"));
	else
		path = s().copy(path);
	err = chdir(path);
	if (path)
		free(path);
	return (err);
}
