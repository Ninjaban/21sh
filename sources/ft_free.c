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

void			ft_free_cmds(t_cmd **cmds)
{
	int			n;

	n = 0;
	if (cmds)
	{
		while (cmds[n])
		{
			free(cmds[n]->name);
			ft_free_tab(cmds[n]->argv);
			free(cmds[n++]);
		}
		free(cmds);
	}
}
