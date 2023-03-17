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

void print_tokens()
{
    t_elems *c;
    int i = 0;

    c = (array(minishell()->tokens)->begin);
    while (c)
    {
        printf("Token %d: %s\n", i, ((t_token *)(c->content))->token);
        c = c->next;
        i++;
    }
}


int main(int argc, char **argv, char **envp)
{
    if (argc != 1)
        exit(1);

//
//
    (void)argv;
    (void)envp;

    init_minishell(envp);
	char *str;
	char *temp;
	int c;
    t_dict *symbol;
    t_tree *temp_tree;
    t_tree *root = array(minishell()->symbols)->root;
	signals_hand();
    export("C=TH");

    while (1)
    {
		str = readline("not bash>");
		if (!str)
			ft_exit(0);
        temp = str;
        while (*temp)
        {
            temp_tree = array(minishell()->symbols)->search_tree(root, temp);
            if (temp_tree) {
                symbol = temp_tree->content;
                printf("%s\n", (char *) symbol->state(&temp, 1));
            }
            else
            {
                c = 0;
                while (*(temp + c) && *(temp + c) != ' ' && !array(minishell()->symbols)->search_tree(NULL, temp + c))
                    c++;
                array(minishell()->tokens)->add(c_token(strings().copy_n(temp, c), CMD));
                temp += c;
            }
            if (!*temp)
                break ;
            if (!array(minishell()->symbols)->search_tree(root, temp))
                temp++;
        }
        print_tokens();
		free(str);
    }
//
//
//    char *t = strings().copy("<$PAa'a'$C");
//    char *temp = t;
//    printf("%s\n", t);
//    symbol = array(minishell()->symbols)->search_tree(root, t)->content;
//    printf("%s\n", (char *)symbol->state(&t, 1));
//    free (temp);
//     printf("temp: %s\n", temp);
//    array(minishell()->env)->destroy();
}
