/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:14:08 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/01 12:49:42 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "shell.h"
#include "error.h"

static char	*ft_chdir_opt_p(char *path, char opt)
{
	char *tmp;

	tmp = NULL;
	if (opt == 'P')
	{
		ft_putendl("OPTION -P"); // A enlever
		ft_putendl(path); // A enlever
		tmp = realpath(path, tmp);
		free(path);
		path = tmp;
		ft_putendl(path); // A enlever
	}
	return (path);
}

static int	ft_chdir_path(char *path, char ***env, char opt)
{
	path = ft_chdir_opt_p(path, opt);
	if (ft_access_dir(path) == 1)
	{
		ft_set_pwd(&(*env), path);
		chdir(path);
		free(path);
		return (TRUE);
	}
	free(path);
	return (FALSE);
}

static int	ft_set_path(char **path, char *str)
{
	char	*tmp;

	if (ft_strcmp(str, "..") != 0 && ft_strcmp(str, "cd") != 0)
		tmp = ft_path_join(*path, str);
	else
		tmp = ft_getcdir(*path);
	free(*path);
	*path = tmp;
	if (!tmp)
		return (FALSE);
	return (TRUE);
}

static int	ft_init_chdir_path(char **tab, char ***env, char opt)
{
	int		n;
	char	**path;

	n = -1;
	if ((path = ft_strsplit((*env)[ft_fpath((*env), "PWD=")], "=")) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	while (tab[++n])
		if ((ft_strcmp(tab[n], ".") != 0) &&
			(ft_set_path(&(path[1]), tab[n]) == FALSE))
		{
			ft_error(ERROR_ALLOC);
			return (FALSE);
		}
	ft_chdir_path(ft_strdup(path[1]), &(*env), opt);
	ft_free_tab(path);
	return (TRUE);
}

static int	ft_old(char ***env, int opt)
{
	char	**old;

	if (ft_fpath((*env), "OLDPWD=") == ft_tablen((*env)))
	{
		ft_error(ERROR_ENV);
		return (FALSE);
	}
	if ((old = ft_strsplit((*env)[ft_fpath((*env), "OLDPWD=")], "=")) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	if (ft_set_pwd(&(*env), old[1]) == FALSE)
	{
		ft_free_tab(old);
		return (FALSE);
	}
	old[1] = ft_chdir_opt_p(old[1], opt);
	chdir(old[1]);
	ft_free_tab(old);
	return (TRUE);
}

static char	ft_chdir_opt(char *arg)
{
	char	opt;
	int		n;

	opt = 'L';
	n = 1;
	while (arg[n])
	{
		if (arg[n] == 'L' || arg[n] == 'P')
			opt = arg[n];
		else
			return (-1);
		n++;
	}
	return (opt);
}

static int	ft_chdir_options(char **argv, char *opt)
{
	int	n;

	*opt = 'L';
	n = 1;
	while (argv[n] && argv[n][0] == '-' && ft_strcmp(argv[n], "-") != 0)
	{
		if ((*opt = ft_chdir_opt(argv[n])) < 0)
		{
			ft_error(ERROR_OPTION);
			return (FALSE);
		}
		n++;
	}
	return (n);
}

int			ft_chdir(char ***env, char **argv)
{
	char		**tab;
	char		*str;
	char		opt;
	int			n;

	n = ft_chdir_options(argv, &opt);
	str = argv[n];
	if (ft_fpath(*env, "PWD=") == ft_tablen(*env))
	{
		ft_error(ERROR_ENV);
		return (FALSE);
	}
	if (!str)
		return (ft_chdir_path(ft_getenv(*env, "HOME="), &(*env), opt));
	if (ft_strcmp(str, "-") == 0)
		return (ft_old(&(*env), opt));
	if (str[0] == '/')
		return (ft_chdir_path(ft_strdup(str), &(*env), opt));
	if ((tab = ft_strsplit(str, "/")) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	ft_init_chdir_path(tab, &(*env), opt);
	ft_free_tab(tab);
	return (TRUE);
}
