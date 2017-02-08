/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:54:30 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/20 11:16:14 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int			ft_builtins(t_cmd *cmds, t_sys **sys)
{
	if (ft_strcmp(cmds->name, "echo") == 0)
		ft_echo(cmds->argv);
	else if ((ft_strcmp(cmds->name, "setenv") == 0) ||
			(ft_strcmp(cmds->name, "export") == 0))
		ft_setenv(cmds->argv[1], &((*sys)->env), FALSE);
	else if (ft_strcmp(cmds->name, "unsetenv") == 0)
		ft_unsetenv(&((*sys)->env), cmds->argv[1]);
	else if (ft_strcmp(cmds->name, "env") == 0)
		ft_env(cmds->argv, (*sys)->env);
	else if (ft_strcmp(cmds->name, "cd") == 0)
		ft_chdir(&((*sys)->env), cmds->argv[1]);
	else if (ft_strcmp(cmds->name, "alias") == 0)
		ft_alias(cmds, &((*sys)->alias));
	else if (ft_strcmp(cmds->name, "unalias") == 0)
		ft_unalias(cmds, &((*sys)->alias));
	else
		return (FALSE);
	return (TRUE);
}
