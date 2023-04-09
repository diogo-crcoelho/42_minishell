/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:19:33 by mvenanci          #+#    #+#             */
/*   Updated: 2023/04/09 18:41:56 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_utils.h"

t_tree	*find_leaf(t_tree *temp, void *cont, int (*cmp)(void *cont1,
				void *cont2));
t_array	**__this(void);
t_tree	*__search_tree(t_tree *root, void *cont);

void	__del_root(void)
{
	t_tree	*lower_leaf;

	if ((*__this())->root->left && (*__this())->root->right)
	{
		lower_leaf = find_leaf((*__this())->root->right,
								(*__this())->root->cont,
								(*__this())->cmp);
		lower_leaf->right = (*__this())->root->left;
		(*__this())->root->left->up = lower_leaf;
		(*__this())->root = (*__this())->root->right;
	}
	else if ((*__this())->root->left)
		(*__this())->root = (*__this())->root->left;
	else if ((*__this())->root->right)
		(*__this())->root = (*__this())->root->right;
}

void	__del_from_tree_cut_lines(t_tree *to_del, t_tree *lower)
{
	if (to_del->up->left == to_del)
		to_del->up->left = lower;
	else
		to_del->up->right = lower;
}

void	__del_from_tree(void *cont)
{
	t_tree	*to_del;
	t_tree	*temp;

	to_del = __search_tree((*__this())->root, cont);
	if (to_del == (*__this())->root)
		__del_root();
	else if (!to_del->right && to_del->left)
	{
		__del_from_tree_cut_lines(to_del, to_del->left);
		to_del->left->up = to_del->up;
	}
	else if (to_del->right && !to_del->left)
	{
		__del_from_tree_cut_lines(to_del, to_del->right);
		to_del->right->up = to_del->up;
	}
	else if (to_del->right && to_del->left)
	{
		temp = to_del;
		to_del = find_leaf(to_del->right, to_del->cont, (*__this())->cmp);
		temp->cont = to_del->cont;
		__del_from_tree_cut_lines(to_del, NULL);
	}
	else
		__del_from_tree_cut_lines(to_del, NULL);
	free(to_del);
}

void	__destroy_tree(t_tree *root)
{
	if (root->left)
		__destroy_tree(root->left);
	if (root->right)
		__destroy_tree(root->right);
	if (!root->left && !root->right)
	{
		if (root->up && root == root->up->left)
			root->up->left = NULL;
		if (root->up && root == root->up->right)
			root->up->right = NULL;
		free(root);
	}
	return ;
}
