/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:31:16 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/02/10 00:56:10 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>



//TODO


//ideias a propor ao miguel
//
// comecar por retirar as aspas -> guardar tudo o que esta dentro de aspas dentro de uma string.
//e so depois trtar dos valores dentro da string. $ e o caralho

//So e considerado novo comando se estiver a seguir a uma pipe.
//  echo echo ls, so deve fazer echo como se fosse uma string e nao xecutar varios comandos.

// Cores fica sempre nice!!



int main()
{
	char *str;
	while (1)
	{
		str = readline("Soups>");
		if (str)
			printf("%s\n", str);
		free(str);
	}
}