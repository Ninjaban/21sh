/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 09:29:30 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/21 10:14:29 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"
#include "terms.h"

static int	ft_check_env(char **env)
{
	if (!env || !(env[0]) ||
		ft_fpath(env, "PWD=") == ft_tablen(env) ||
		ft_fpath(env, "HOME=") == ft_tablen(env))
		return (FALSE);
	return (TRUE);
}

static char	**ft_tabcpy(char **t)
{
	char	**cpy;
	int		n;

	n = 0;
	if (ft_check_env(t) == FALSE)
		return (NULL);
	if ((cpy = malloc(sizeof(char *) * (ft_tablen(t) + 1))) == NULL)
	{
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (NULL);
	}
	while (t[n])
		cpy[n++] = NULL;
	cpy[n] = NULL;
	n = -1;
	while (t[++n])
		if ((cpy[n] = ft_strdup(t[n])) == NULL)
		{
			ft_log(TYPE_ERROR, ERROR_ALLOC);
			ft_free_tab(cpy);
			return (NULL);
		}
	return (cpy);
}

int			main(int ac, char **av, char **env)
{
	t_sys	*sys;

	(void)ac;
	(void)av;
	if (ft_sys_init(&sys) == 1)
		return (ft_error_int(ERROR_LAUNCH, 1));
	if (ft_termcaps_init(&sys->term_new, &sys->term_save) == FALSE)
	{
		ft_log(TYPE_WARNING, ERROR_TERM);
		return (ft_error_int(ERROR_LAUNCH, 1));
	}
	if ((sys->env = ft_tabcpy(env)) == NULL)
	{
		ft_log(TYPE_WARNING, ERROR_ENV);
		return (ft_error_int(ERROR_LAUNCH, 1));
	}
	if (ft_signal_stop() == FALSE)
		return (1);
	ft_shell(sys, FALSE, NULL, NULL);
	return (0);
}
