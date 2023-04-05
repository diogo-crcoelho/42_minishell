void	free_pp(void *pp);
void	free_pp(void *pp);
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci <mvenanci@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:47:30 by mvenanci          #+#    #+#             */
/*   Updated: 2023/03/27 15:47:52 by mvenanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int s_exit(int sc)
{
    destroy_m();
//	m()->exit_status = sc;
//    printf("inside %d\n", sc);
    exit(sc);
}

void exit_err(char *err1, char *err2, char *val)
{
    char *total;

    total = s().join(err1, err2, val);
    write(2, total, s().len(total, 0));
    free(total);
    s_exit(2);
}

long s_atoi(char *str)
{
    long old;
    long val;
    int signal;
    int i;

    i = -1;
    val = 0;
    signal = 1;
    if (!s().equal(str, "-9223372036854775808"))
        return (LONG_MIN);
    if (*str == '-' || *str == '+')
        if (*str++ == '-')
            signal *= -1;
    while(str && str[++i])
    {
        old = val;
        val = val * 10 + (str[i] -48);
        if (val < old || !__isdigit(str[i]))
            exit_err("exit: ", ": numeric argument required\n", str);
    }
    return (val * signal);
}

int parse_exit(long value)
{
    if (LONG_MIN == value)
        return (0);
    value = value % 256;
    return value;
}
int	ft_exit(void *cont)
{
    char **vars;
    int ret;

    vars = (char **)cont;
    if (vars[1])
    {
        cona("exit: too many arguments");
        return 1;
    }
    if (!vars[0])
        vars[0] = "0";
    ret = parse_exit(s_atoi(vars[0]));
//    free_pp(cont);
	s_exit(ret);
    return (0);
}