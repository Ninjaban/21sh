/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 10:29:27 by mrajaona          #+#    #+#             */
/*   Updated: 2016/12/22 10:45:53 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

/*
** new < node -> left
** new >= node -> right
*/

static void	insert_data(t_btree *new, t_btree *node, int (cmpf)(void *, void *))
{
	if (cmpf(new->item, node->item) < 0)
	{
		if (node->left == NULL)
			node->left = new;
		else if (cmpf(new->item, node->left->item) >= 0)
		{
			new->left = node->left;
			node->left = new;
		}
		else
			insert_data(new, node->left, cmpf);
	}
	else
	{
		if (node->right == NULL)
			node->right = new;
		else if (cmpf(new->item, node->left->item) < 0)
		{
			new->right = node->right;
			node->right = new;
		}
		else
			insert_data(new, node->right, cmpf);
	}
}

void		btree_insert_data(t_btree **root, void *item,
								int (cmpf)(void *, void *))
{
	t_btree	*new;

	new = btree_create_node(item);
	if (*root == NULL)
		*root = new;
	else
		insert_data(new, *root, cmpf);
}
