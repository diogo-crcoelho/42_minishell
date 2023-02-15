/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:00:37 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/02/10 20:34:09 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// Podemos implementar o cd -...
// like guradarmos na estrutura global o caminho atual sempre que chamarmos o cd

int cd(char *path)
{
    int err;

    if (!strings().len(path, 0))
        path = strings().copy(getenv("HOME"));
    else if(!strings().equal_n(path, "~", 1))
        path = strings().join(getenv("HOME"), &path[1], 0);
    else
        path = strings().copy(path);
    err = chdir(path);
    if (path)
        free(path);
    return err;
}
