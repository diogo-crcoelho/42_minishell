//
// Created by dcarvalh on 2/16/23.
//

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
	t_elems *teste;
	int i;

	if (!strings().equal_n(str, "~", 1))
		return (strings().join(getenv("HOME"), &str[1], 0));
	else if (!strings().equal_n(str, "$", 1) && (str[1]) != '?')
	{
		i = strings().alnum(&str[1]);
		if (!i)
			i = strings().len(&str[1], 0);
		teste = array(minishell()->env)->search(cmp, str + 1, i);
		if (teste)
		{
			if (str[++i])
				return (strings().join(((t_env *)teste->content)->splitted[1],
						&str[i], 0));
			return (strings().copy(((t_env *)teste->content)->splitted[1]));
		}
		else
			return (strings().copy(""));
	}
	else if (!strings().equal_n(str, "$", 1))
		return (ft_itoa(minishell()->exit_status));
	return (strings().copy(str));
}