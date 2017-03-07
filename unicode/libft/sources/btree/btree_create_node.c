/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 09:26:30 by mrajaona          #+#    #+#             */
/*   Updated: 2016/07/21 09:46:21 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*btree_create_node(void *item)
{
	t_btree	*new;

	if ((new = (t_btree *)malloc(sizeof(t_btree))) == NULL)
		return (NULL);
	new->item = item;
	new->left = 0;
	new->right = 0;
	return (new);
}
