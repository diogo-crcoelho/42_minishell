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

    arr = ft_calloc(((*__this())->size + 1) * sizeof(void *));
	temp = (*__this())->begin;
	i = 0;
	while (temp)
	{
		arr[i++] = temp->content;
		temp = temp->next;
	}
	return (arr);
}

t_tree  *find_leaf(t_tree *temp, void *content, int (*cmp)(void *cont1, void *cont2))
{
    t_tree  *leaf;

    if (cmp(temp->content, content) < 0 && temp->right)
        leaf = find_leaf(temp->right, content, cmp);
    else if (cmp(temp->content, content) < 0 && !temp->right)
        return (temp);
    else if (cmp(temp->content, content) > 0 && temp->left)
        leaf = find_leaf(temp->left, content, cmp);
    else
        return (temp);
    return (leaf);
}

t_tree  *__add_leaf(void *content)
{
    t_tree  *new;
    t_tree  *temp;

    temp = (*__this())->root;
    new = ft_calloc(sizeof(t_tree));
    new->content = content;
    if (!(*__this())->root)
        (*__this())->root = new;
    else
    {
        temp = find_leaf(temp, content, (*__this())->cmp);
        if ( (*__this())->cmp(temp->content, content) <= 0)
            temp->right = new;
        else
            temp->left = new;
        new->up = temp;
    }
    return (new);
}

void    __build_tree(void)
{
    t_elems *temp;

    temp = (*__this())->begin;
    while (temp)
    {
        (*__this())->add_leaf(temp->content);
        temp = temp->next;
    }
}

t_tree   *__search_tree(void *content)
{
    return (find_leaf((*__this())->root, content, (*__this())->cmp));
}

void    _del_from_tree(void *content)
{
    t_tree  *to_del;
    t_tree  *temp;

    to_del = find_leaf((*__this())->root, content, (*__this())->cmp);
    if (!to_del->right && to_del->left)
    {
        to_del->up->left = to_del->left;
        to_del->left->up = to_del->up;
    }
    else if (to_del->right && !to_del->left)
    {
        to_del->up->right = to_del->right;
        to_del->right->up = to_del->up;
    }
    else if (to_del->right && to_del->left)
    {
        temp = to_del;
        to_del = find_leaf(to_del->left, to_del->content, (*__this())->cmp);
        temp->content = to_del->content;
    }
    free(to_del);
}