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

void	pipex();

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

void print_cmds(void);

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
        printf("Token %d: %s, type=%d\n", i, ((t_token *)(c->content))->token, ((t_token *)(c->content))->type);
        c = c->next;
        i++;
    }
}

int add_space(char *s)
{
    if (*s == '|' || !*s)
        return (0);
    else if (((t_token *)array(minishell()->tokens)->end->content)->type == PIPE)
        return (0);
    return (1);
}

void    lex(char **temp)
{
    t_dict *symbol;

    while (**temp)
    {
        symbol = (t_dict *) array(minishell()->symbols)->search_tree(NULL, *temp);
        if(check_tilde(temp))
            continue ;
        if (symbol)
        {
            symbol = ((t_tree *) symbol)->content;
            symbol->state(temp, 1);
            continue;
        }
        else if (**temp && **temp != ' ' && **temp != '|')
            non_symbol_state(temp, 1);
        while (**temp == ' ' || (add_space(*temp) && !array(minishell()->tokens)->add(c_token(" ", SPC))))
            (*temp)++;
        if (**temp == '|' && array(minishell()->tokens)->add(c_token("|", PIPE)))
            (*temp)++;
    }
//    print_tokens();
}

int main(int argc, char **argv, char **envp)
{
    if (argc != 1)
        exit(1);

    (void)argv;
    (void)envp;
    init_minishell(envp);
	char *str;
	char *temp;
    export("C=TH");
    while (1)
    {
        signals_hand();
        str = readline("not bash>");
		if (!str)
			ft_exit(0);
        temp = str;
        lex(&temp);
        delexer();
        print_cmds();
        pipex();
        array(minishell()->tokens)->destroy();
        minishell()->tokens = creat_array();
        array(minishell()->cmds)->destroy();
        minishell()->cmds = creat_array();
		free(str);
    }

}
