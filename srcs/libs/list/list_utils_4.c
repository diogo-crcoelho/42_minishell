//
// Created by miguel on 16-02-2023.
//

#include "list_utils.h"

t_tree  *find_leaf(t_tree *temp, void *content, int (*cmp)(void *cont1, void *cont2));

void    __del_root(void)
{
    t_tree  *lower_leaf;

    if ((*__this())->root->left && (*__this())->root->right)
    {
        lower_leaf = find_leaf((*__this())->root->right, (*__this())->root->content, (*__this())->cmp));
        lower_leaf->right = (*__this())->root->left;
        (*__this())->root->left->up = lower_leaf;
    }
    else if ((*__this())->root->left)
        (*__this())->root = (*__this())->root->left;
    else if ((*__this())->root->right)
        (*__this())->root = (*__this())->root->right;
}

void    __del_from_tree(void *content)
{
    t_tree  *to_del;
    t_tree  *temp;

    to_del = find_leaf((*__this())->root, content, (*__this())->cmp);
    if (to_del == (*__this())->root)
        __del_root():
    else if (!to_del->right && to_del->left)
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