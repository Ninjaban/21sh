/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 20:08:45 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 20:09:38 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void			ft_free_tab(char **tab)
{
	size_t		n;

	n = 0;
	if (tab)
	{
		while (tab[n])
			free(tab[n++]);
		free(tab);
	}
}

void			ft_free(t_cmd **cmds, char **str, t_btree **cmd)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	if (cmds && *cmds)
	{
		free((*cmds)->name);
		ft_free_tab((*cmds)->argv);
		free(*cmds);
		*cmds = NULL;
	}
	if (cmd && *cmd)
	{
		btree_apply_suffix(*cmd, &ft_delete_node);
	}
}
