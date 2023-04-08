/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:47:30 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/08 18:25:31 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	s_exit(int sc)
{
	destroy_m();
	exit(sc);
}

void	exit_err(char *err1, char *err2, char *val)
{
	char	*total;

	total = s().join(err1, err2, val);
	write(2, total, s().len(total, 0));
	free(total);
	s_exit(2);
}

long	s_atoi(char *str)
{
	long	old;
	long	val;
	int		signal;
	int		i;

	i = -1;
	val = 0;
	signal = 1;
	if (!s().len(str, 0))
		exit_err("exit: ", ": numeric argument required\n", str);
	if (!s().equal(str, "-9223372036854775808"))
		return (LONG_MIN);
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			signal *= -1;
	while (str && str[++i])
	{
		old = val;
		val = val * 10 + (str[i] - 48);
		if (val < old || !__isdigit(str[i]))
			exit_err("exit: ", ": numeric argument required\n", str);
	}
	return (val * signal);
}

int	parse_exit(long value)
{
	if (LONG_MIN == value)
		return (0);
	value = value % 256;
	return (value);
}

int	ft_exit(void *cont, int fd)
{
	char	**vars;
	int		ret;

	(void)fd;
	vars = (char **)cont;
	if (s().len(vars[0], 0) && vars[1])
	{
		cona("exit: too many arguments\n");
		return (1);
	}
	if (!s().len(vars[0], 0))
		s_exit(0);
	ret = parse_exit(s_atoi(vars[0]));
	s_exit(ret);
	return (0);
}
