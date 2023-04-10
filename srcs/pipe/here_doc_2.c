/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:08:49 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/04/10 20:10:21 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_lines_cut_lines(char *str, char **tmp)
{
	char	*str2;
	char	*var;

	str2 = str;
	var = var_state(tmp, 0);
	str = s().join(str, var, "");
	free(str2);
	free(var);
	return (str);
}
