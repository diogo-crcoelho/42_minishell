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


// Para discutir com o MIGUEL::
//Sera que vale a pena estar a meter as condicoes do ~ do cd ouo qd virmos o til damos logo replace!!!

//https://web.mit.edu/gnu/doc/html/rlman_2.html -> for keybindings etc


// Caracteres a ter cuidado..
/* |
 * ""
 * ''
 *
 * $
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
    init_minishell(envp);
    env();
//    array(minishell()->env)->cmp = cmp_env;
//    array(minishell()->env)->build_tree();
//    printf("%s\n", ((t_env *)array(minishell()->env)->root->content)->total);
//    t_tree  *test = array(minishell()->env)->search_tree(array(minishell()->env)->root, array(minishell()->env)->begin->content);
////    t_elems *temp = array(minishell()->env)->search(cmp, ((t_env *)array(minishell()->env)->root->content)->total, 1000);
//    printf("%s\n", ((t_env *)test->content)->total);
////    array(minishell()->env)->remove(temp);
//    printf("%s\n", ((t_env *)array(minishell()->env)->root->content)->total);

//    char fuck[5] = "$ABC";
//
    char **teste = ft_calloc(2 * sizeof(char *));

    teste[0] = expand("$ABC");
    export("ABC=Fuck this shit im out");
    env();
    export("DD=Odeio esta merda");
    echo(teste, 1);
//    pwd();
//    cd(NULL);
//    free (str);
//    pwd();
//    echo(NULL, 1);
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
