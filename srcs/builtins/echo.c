#include "../../incs/minishell.h"

void	echo(char *s, int flag)
{
	printf("%s", s);
	if (flag)
		printf("\n");
}