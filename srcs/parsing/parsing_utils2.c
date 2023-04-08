/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:33:27 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/08 17:01:10 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static size_t	digit_count(long int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
	{
		++i;
		n *= -1;
	}
	while (n > 0)
	{
		++i;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*res;
	size_t		size;
	long int	temp;

	temp = (long)n;
	size = digit_count(temp);
	res = (char *)malloc(size + 1);
	if (!res)
		return (NULL);
	res[size] = 0;
	if (temp == 0)
		res[0] = 48;
	if (temp < 0)
	{
		res[0] = '-';
		temp *= -1;
	}
	while (temp > 0)
	{
		res[--size] = temp % 10 + 48;
		temp /= 10;
	}
	return (res);
}

char	*expand(char *str)
{
	t_elems	*teste;
	int		i;

	if (!s().equal_n(str, "~", 1))
		return (s().join(getenv("HOME"), &str[1], 0));
	else if (!s().equal_n(str, "$", 1) && (str[1]) != '?')
	{
		i = s().alnum(&str[1]);
		if (!i)
			i = s().len(&str[1], 0);
		teste = array(m()->env)->search(comp_var, str + 1);
		if (teste)
		{
			if (str[++i])
				return (s().join(((t_env *)teste->cont)->splitted[1],
									&str[i],
									0));
			return (s().copy(((t_env *)teste->cont)->splitted[1]));
		}
		else
			return (s().copy(""));
	}
	else if (!s().equal_n(str, "$", 1))
		return (ft_itoa(m()->exit_status));
	return (s().copy(str));
}
