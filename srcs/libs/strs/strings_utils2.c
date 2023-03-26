//
// Created by dcarvalh on 2/16/23.
//

#include "ft_strings.h"

static int	__isalpha(int c)
{
	if (c < 65 || c > 122)
		return (0);
	if (c > 90 && c < 97)
		return (0);
	return (1);
}

static int	__isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

int	__isal_num(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (!__isdigit(str[i]) && !__isalpha(str[i]))
			return (i);
	return (0);
}

char	*__append(char *s, char c)
{
	char	*new;
	int		i;

	i = -1;
	new = ft_calloc(strings().len(s, 0) + 2);
	while (s[++i])
		new[i] = s[i];
	new[i] = c;
	return (new);
}
