/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:31:16 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/02/20 13:21:08 by dcarvalh         ###   ########.fr       */
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


// Para discutir com o MIGUEL::
//Sera que vale a pena estar a meter as condicoes do ~ do cd ouo qd virmos o til damos logo replace!!!

//https://web.mit.edu/gnu/doc/html/rlman_2.html -> for keybindings etc


// Caracteres a ter cuidado..
/* |
 * ""
 * ''
 *
 * $ e ~
 *<< e >>
 *< e >
 *
 */

t_mini 	*minishell(void)
{
	static t_mini a;

	return (&a);
}

int cmp_env(void *cont1, void *cont2)
{
    char    *s1 = ((t_env *)cont1)->total;
    char    *s2 = ((t_env *)cont2)->total;
    return (strings().equal(s1, s2));
}

int main(int argc, char **argv, char **envp)
{
    if (argc != 1)
        exit(1);
//    char *str =  strings().copy("");


    (void)argv;
    (void)envp;

    // init_minishell(envp);
//     char *s = strings().copy("$test");
//     char *temp;
// //    t_dict teste = {s, 0, 0};
//     t_tree *symbol;
//     temp = NULL;
	char *str;
	signals_hand();
    while (1)
    {
		str = readline("not bash>");
		if (!str)
			ft_exit(0);
		printf("%s\n", str);
		free(str);
    }
    // printf("temp: %s\n", temp);
    array(minishell()->env)->destroy();
}
