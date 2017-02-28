/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/11 08:42:36 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int				ft_true_node(void *root, void *item)
{
	if (((t_btree *)root)->right &&
			(((t_node *)(((t_btree *)root)->item))->node == CMD ||
			((t_node *)(((t_btree *)root)->item))->node == AND ||
			((t_node *)(((t_btree *)root)->item))->node == OR))
		return (0);
	if (((t_btree *)root)->left)
		return (-1);
	if (((t_node *)(((t_btree *)item)->item))->redir != FALSE)
		return (-1);
	if (!((t_btree *)root)->right)
		return ((((t_node *)(((t_btree *)root)->item))->node == TRUE) ? 0 : -1);
	return (-1);
}

int				ft_false_node(void *root, void *item)
{
	(void)root;
	(void)item;
	return (0);
}
