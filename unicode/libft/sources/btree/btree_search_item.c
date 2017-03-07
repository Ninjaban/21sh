/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 10:54:47 by mrajaona          #+#    #+#             */
/*   Updated: 2016/12/22 10:43:52 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	*btree_search_item(t_btree *root, void *data_ref,
							int (*cmpf)(void *, void *))
{
	int	n;

	if (root == NULL)
		return (NULL);
	n = cmpf(root->item, data_ref);
	if (n < 0 && root->left)
		btree_search_item(root->left, data_ref, cmpf);
	else if (n == 0)
		return (root->item);
	else if (n > 0 && root->right)
		btree_search_item(root->right, data_ref, cmpf);
	return (NULL);
}
