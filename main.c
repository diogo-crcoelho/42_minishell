
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

int main()
{
    t_func stringss = (void *)s()->len;

    t_s *a = ((t_s*)stringss());
    printf("%d\n", (int)((long)stringss("Hello", 0)));
}