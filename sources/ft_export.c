/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:05:48 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/09 12:29:09 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static size_t	ft_find_path(char **env, char *str)
{
	size_t	n;

	n = 0;
	while (env[n])
		if (ft_strncmp(env[n++], str, ft_strlen(str) - 1) == 0)
			return (n - 1);
	return (n);
}

static void		ft_export_env(char ***env, char opt)
{
	size_t	n;

	n = 0;
	while ((*env)[n])
	{
		if (opt == 'p')
			ft_putstr("export ");
		ft_putendl((*env)[n]);
		n++;
	}
}

static int		ft_export_print(char *str, char ***env, char opt)
{
	size_t	n;
	char	**tab;

	n = 0;
	if (!str)
		ft_export_env(env, opt);
	else
	{
		if ((tab = ft_strsplit(str, "=")) == NULL)
			return (ft_error_int(ERROR_ALLOC, FALSE));
		n = ft_find_path(*env, tab[0]);
		ft_free_tab(tab);
		if (n == ft_tablen(*env))
			return (ft_error_int(ERROR_VNOTFOUND, FALSE));
		else
		{
			ft_putstr("export ");
			ft_putendl((*env)[n]);
		}
	}
	return (TRUE);
}

static int		ft_export_opt(size_t *x, char *opt, char **cmd)
{
	size_t	n;

	while (cmd[++(*x)] && cmd[*x][0] == '-')
	{
		n = 0;
		while (cmd[*x][++n])
		{
			if (cmd[*x][n] == 'p')
				*opt = 'p';
			else
				return (ft_error_int(ERROR_OPTION, FALSE));
		}
	}
	return (TRUE);
}

int				ft_export(char **cmd, char ***env, char ***shvar)
{
	size_t	x;
	int		err;
	char	opt;

	x = 0;
	opt = 0;
	err = TRUE;
	if (ft_export_opt(&x, &opt, cmd) != TRUE)
		return (FALSE);
	if (cmd[x])
	{
		while (cmd[x])
		{
			if (opt == 'p' && err == TRUE)
				err = ft_export_print(cmd[x], env, opt);
			else
				ft_setenv(cmd[x], env, shvar, FALSE);
			x++;
		}
	}
	else
		ft_export_print(NULL, env, opt);
	return (err);
}
