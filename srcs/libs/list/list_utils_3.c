//
// Created by mvenanci on 2/13/23.
//

#include "list_utils.h"

t_array	**__this(void);

void	**__to_array(void)
{
	void	**arr;
	t_elems *temp;
	int		i;

	arr = ft_calloc((*__this())->size);
	temp = (*__this())->begin;
	i = 0;
	while (temp)
	{
		arr[i++] = temp->content;
		temp = temp->next;
	}
	return (arr);
}