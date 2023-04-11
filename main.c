
// C Program to design a shell in Linux
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#include "./incs/minishell.h"
typedef 	void *(*t_func)();

void	*ft_calloc(size_t size)
{
    void	*ptr;
    size_t	i;

    ptr = malloc(size);
    if (!ptr)
        exit(!write(2, "Memmory error\n", 14));
    i = -1;
    if (size != 0)
        while (++i < size)
            ((char *)ptr)[i] = 0;
    return (ptr);
}

char	**rec_split(char **splited, int words, char c, const char *s)
{
	char	*word;
	int		i;

	i = 0;
	while (s && *s && *s == c)
		s++;
	while (s && s[i] && s[i] != c)
		i++;
	word = NULL;
	if (i)
	{
		word = ft_calloc(i + 1);
		while (*s && *s != c)
			*word++ = *s++;
	}
	if (word)
		splited = rec_split(splited, words + 1, c, s);
	else if (!*s)
		splited = ft_calloc(sizeof(char *) * (words + 1));
	splited[words] = word - i;
	return (splited);
}

char	**ft_split(const char *s, char c)
{
	return (rec_split(0, 0, c, s));
}


int main()
{
    char **str = ft_split("ls\e\0\e", '\e');

	execve("/usr/bin/ls", str, NULL);
}