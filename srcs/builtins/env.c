/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:37:43 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/02/10 20:39:11 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int env(char **envp)
{
	int i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}