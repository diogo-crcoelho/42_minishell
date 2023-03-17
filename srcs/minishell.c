/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:31:16 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/02/20 14:17:02 by dcarvalh         ###   ########.fr       */
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

    init_minishell(envp);
//     char *s = strings().copy("$test");
//     char *temp;
// //    t_dict teste = {s, 0, 0};
//     t_tree *symbol;
//     temp = NULL;
//	char *str;
//	export("ABC=teste");
//	signals_hand();
//	export_empty(array(minishell()->env)->root);
//	env();
//    while (1)
//    {
//		str = readline("not bash>");
//		if (!str)
//			ft_exit(0);
//		printf("%s\n", str);
//		free(str);
//    }
//    array(minishell()->tokens)->add(c_token("ABC", 1));
    array(minishell()->tokens)->add(c_token("teste.txt", 2));
    array(minishell()->tokens)->add(c_token("Makefile", 1));
    array(minishell()->tokens)->add(c_token("cat", 4));
    array(minishell()->tokens)->add(c_token(" -e", 4));
    array(minishell()->tokens)->add(c_token(" -f", 2));
    array(minishell()->tokens)->add(c_token("|", 6));
    array(minishell()->tokens)->add(c_token("grep", 4));
    array(minishell()->tokens)->add(c_token("main", 4));
    delexer();

    t_elems *teste = array(minishell()->cmds)->begin;
    while(teste)
    {
        printf("infile: %d\n", ((t_cmd *)teste->content)->fd_red[0]);
        printf("outfile: %d\n", ((t_cmd *)teste->content)->fd_red[1]);
        char **strs =  ((t_cmd *)teste->content)->args;
        printf("cmds: ");
        while(*strs)
            printf("%s ", *strs++);
        printf("\n");
        teste = teste->next;
    }
    // printf("temp: %s\n", temp);
    array(minishell()->env)->destroy();
}
