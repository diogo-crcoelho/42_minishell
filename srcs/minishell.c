/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:31:16 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/02/10 20:39:35 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//TODO


//ideias a propor ao Miguel
//
// comecar por retirar as aspas -> guardar tudo o que esta dentro de aspas dentro de uma string.
//e so depois trtar dos valores dentro da string. $ e o caralho

//So e considerado novo comando se estiver a seguir a uma pipe.
//  echo echo ls, so deve fazer echo como se fosse uma string e nao xecutar varios comandos.

// Cores fica sempre nice!!

//https://web.mit.edu/gnu/doc/html/rlman_2.html -> for keybindings etc


t_mini 	*minishell(void)
{
	static t_mini a;

	return (&a);
}

int main(int argc, char **argv, char **envp)
{
    if (argc != 1)
        exit(1);
//    char *str;
    (void)argv;
    init_minishell(envp);
//    env();
        printf("\n\n");
//   export("LOVE===ROSINHA");
//    export("ABC=DEF");
//    export("LOVE====Pequena=Rosinha");
//    env();
//    unset("ABC");
//    env();

//	while (1)
//	{
//        str = readline("\nnot-bash>");
//        if (str){
//            init_parse(str);  //still needs parsing
//            if (strings().equal(str, "exit\n")) {
//                break;
//            }
//        }
//        free(str);
//    }
    array(minishell()->env)->destroy();
}
