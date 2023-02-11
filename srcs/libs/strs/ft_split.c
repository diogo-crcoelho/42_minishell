/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:09:06 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/02/09 17:29:01 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

char	**rec_split(char **splited, int words, char c, const char *s)
{
    char	*word;
    int		i;

    i = 0;
    while (*s && *s == c)
        s++;
    while (s[i] && s[i] != c)
        i++;
    word = NULL;
    if (i)
    {
        word = ft_calloc(i + 1);
        while (*s && *s != c)
            *word++ = *s++;
    }
    if (*s == c)
        splited = rec_split(splited, words + 1, c, s);
    else if (!*s)
        splited = ft_calloc(sizeof(char *) * (words + 2));
    splited[words] = word - i;
    return (splited);
}

char	**ft_split(const char *s, char c)
{
    return (rec_split(0, 0, c, s));
}
