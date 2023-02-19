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
    int     val;

    val = cmp(temp->content, content);
    if (val < 0 && temp->right)
        leaf = find_leaf(temp->right, content, cmp);
    else if (val < 0 && !temp->right)
        return (temp);
    else if (val > 0 && temp->left)
        leaf = find_leaf(temp->left, content, cmp);
    else
        return (temp);
    return (leaf);
}

t_tree  *__add_leaf(void *content)
{
    t_tree  *new;
    t_tree  *temp;

    new = ft_calloc(sizeof(t_tree));
    new->content = content;
    if (!(*__this())->root)
        (*__this())->root = new;
    else
    {
        temp = find_leaf((*__this())->root, content, (*__this())->cmp);
        if ((*__this())->cmp(temp->content, content) <= 0)
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

t_tree   *__search_tree(t_tree *root, void *content, int (*cmp)(void *cont1, void *cont2))
{
    t_tree  *elem;
    int     val;

    elem = NULL;
    val = cmp(root->content, content);
    if (val < 0 && root->right)
         elem = __search_tree(root->right, content, cmp);
    else if (val > 0 && root->left)
        elem = __search_tree(root->left, content, cmp);
    else if (val == 0)
        elem = root;
    return (elem);
}
