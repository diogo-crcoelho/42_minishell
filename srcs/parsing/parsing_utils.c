//
// Created by dcarvalh on 2/13/23.
//

#include "../../incs/minishell.h"


void second_parse(char *str)
{
    printf("%s\n", str);
}

void init_parse(const char *str)
{
    char **splitted;
    int     i;

    i = -1;
    splitted = strings().split(str, '|');
    while (splitted[++i])
        second_parse(strings().trim(splitted[i]));
}
