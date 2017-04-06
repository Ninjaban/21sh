/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:54:30 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 10:47:59 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FICHIER :: ft_builtins
**   Forêt de if pour gérer les builtins. caca.
*/

#include "libft.h"
#include "shell.h"

static int	ft_exec_builtins_other(t_cmd *cmds, t_sys **sys)
{
	if (ft_strcmp(cmds->name, "alias") == 0)
		return (ft_alias(cmds, &((*sys)->alias)));
	else if (ft_strcmp(cmds->name, "unalias") == 0)
		return (ft_unalias(cmds, &((*sys)->alias)));
	else if (ft_strcmp(cmds->name, "keymap") == 0)
		return (ft_keymap(&((*sys)->keymap), cmds->argv, *sys));
	else if (ft_strcmp(cmds->name, "history") == 0)
		return (ft_hist_built(cmds->argv, &((*sys)->history)));
	else if (ft_strcmp(cmds->name, "help") == 0)
		return (ft_help(cmds->argv, (*sys)->env, (*sys)->env));
	return (FALSE);
}

int			ft_exec_builtins(t_cmd *cmds, t_sys **sys)
{
	if (ft_strcmp(cmds->name, "echo") == 0)
		return (ft_echo(cmds->argv));
	else if (ft_strcmp(cmds->name, "setenv") == 0)
		return (ft_setenv(cmds->argv[1], &((*sys)->env),
							&((*sys)->shvar), FALSE));
	else if (ft_strcmp(cmds->name, "export") == 0)
		return (ft_export(cmds->argv, &((*sys)->env), &((*sys)->shvar)));
	else if (ft_strcmp(cmds->name, "set") == 0)
		return (ft_set(cmds->argv, &((*sys)->env), &((*sys)->shvar)));
	else if (ft_strcmp(cmds->name, "unset") == 0)
		return (ft_unset(&((*sys)->env), &((*sys)->shvar),
							&((*sys)->ftvar), cmds->argv));
	else if (ft_strcmp(cmds->name, "unsetenv") == 0)
		return (ft_unsetenv(&((*sys)->env), cmds->argv[1]));
	else if (ft_strcmp(cmds->name, "env") == 0)
		return (ft_env(cmds->argv, (*sys)->env, &((*sys)->shvar)));
	else if (ft_strcmp(cmds->name, "cd") == 0)
		return (ft_chdir(&((*sys)->env), &((*sys)->shvar), cmds->argv));
	else if (ft_exec_builtins_other(cmds, &(*sys)) == TRUE)
		return (TRUE);
	else
		return (FALSE);
}

static int	ft_builtins_other(t_cmd *cmds)
{
	if (ft_strcmp(cmds->name, "alias") == 0)
		return (TRUE);
	else if (ft_strcmp(cmds->name, "unalias") == 0)
		return (TRUE);
	else if (ft_strcmp(cmds->name, "keymap") == 0)
		return (TRUE);
	else if (ft_strcmp(cmds->name, "history") == 0)
		return (TRUE);
	else if (ft_strcmp(cmds->name, "help") == 0)
		return (TRUE);
	return (FALSE);
}

int			ft_builtins(t_cmd *cmds)
{
	if (ft_strcmp(cmds->name, "echo") == 0)
		return (TRUE);
	else if ((ft_strcmp(cmds->name, "setenv") == 0) ||
			(ft_strcmp(cmds->name, "export") == 0))
		return (TRUE);
	else if (ft_strcmp(cmds->name, "set") == 0)
		return (TRUE);
	else if (ft_strcmp(cmds->name, "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(cmds->name, "unsetenv") == 0)
		return (TRUE);
	else if (ft_strcmp(cmds->name, "env") == 0)
		return (TRUE);
	else if (ft_strcmp(cmds->name, "cd") == 0)
		return (TRUE);
	else if (ft_builtins_other(cmds) == TRUE)
		return (TRUE);
	else
		return (FALSE);
}
