/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sys.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 10:15:30 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/10 10:59:07 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

int			ft_sys_init(t_sys **sys)
{
	if ((*sys = malloc(sizeof(t_sys))) == NULL)
		return (1);
	(*sys)->env = NULL;
	(*sys)->history = NULL;
	(*sys)->alias = NULL;
	(*sys)->cmds = NULL;
	return (0);
}

void		ft_sys_free(t_sys *sys)
{
	if (sys->env)
		ft_free_tab(sys->env);
	if (sys->history)
		ft_free_tab(sys->history);
	if (sys->alias)
		ft_alias_remove(&(sys->alias));
	if (sys->cmds)
		ft_free_cmds(sys->cmds);
	free(sys);
}
