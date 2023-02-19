/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenanci@student.42lisboa.com <mvenanci    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:25:26 by mvenanci@st       #+#    #+#             */
/*   Updated: 2023/01/21 16:02:58 by mvenanci@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_utils.h"

void	__destroy(void);
t_elems	*__add(void *content);
void	__for_each(void (*func)(t_elems *elem, void *p), void *o);
void	__del(t_elems *elem);
void	**__to_array(void);
void    __build_tree(void);
t_tree   *__search_tree(t_tree *root, void *content, int (*cmp)(void *cont1, void *cont2));
t_tree  *__add_leaf(void *content);

t_array	**__this(void)
{
	static t_array	*a;

	return (&a);
}

t_array	*array(void *lst)
{
	*__this() = lst;
	return (*__this());
}

void	*ft_calloc(size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(size);
	if (!ptr)
		exit (!write(2, "Memmory error\n", 14));
	i = -1;
	if (size != 0)
		while (++i < size)
			((char *)ptr)[i] = 0;
	return (ptr);
}

t_elems *__search(int (*cmp)(void *cont, void *buf, int size),void *buf, int size)
{
	t_elems	*temp;

	temp = (*__this())->begin;
	while (temp)
	{
		if (!cmp(temp->content, buf, size))
			return (temp);
        temp = temp->next;
	}
	return (NULL);
}

void	*creat_array(void)
{
	t_array	*new;

	new = ft_calloc(sizeof(t_array));
	new->add = __add;
	new->remove = __del;
	new->destroy = __destroy;
	new->for_each = __for_each;
	new->search = __search;
	new->to_array = __to_array;
    new->build_tree = __build_tree;
    new->add_leaf = __add_leaf;
    new->search_tree = __search_tree;
	return (new);
}
