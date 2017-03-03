/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:14:08 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/02 14:31:25 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static int	ft_chdir_path(char *path, char **tab, char ***env, char opt)
{
	char	**cdpath;
	int		res;

	res = FALSE;
	cdpath = ft_getcdpath(*env);
	if (path && access(path, F_OK) != 0 && cdpath)
		if ((res = ft_chdir_cdpath(&path, cdpath, tab)) == FALSE)
			return (FALSE);
	if (cdpath)
		ft_free_tab(cdpath);
	if (ft_access_dir(path) == TRUE)
	{
		chdir(path);
		if (opt == 'P')
			path = ft_chdir_opt_p(path, opt);
		ft_set_pwd(&(*env), path);
		if (res == TRUE)
			ft_putendl(path);
		free(path);
		return (TRUE);
	}
	free(path);
	return (FALSE);
}

int			ft_chdir_set_path(char **path, char *str)
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
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (FALSE);
	}
	while (tab[++n])
		if ((ft_strcmp(tab[n], ".") != 0) &&
			(ft_chdir_set_path(&(path[1]), tab[n]) == FALSE))
		{
			ft_log(TYPE_ERROR, ERROR_ALLOC);
			return (FALSE);
		}
	ft_chdir_path(ft_strdup(path[1]), tab, &(*env), opt);
	ft_free_tab(path);
	return (TRUE);
}

static int	ft_old(char ***env, int opt)
{
	char	**old;

	if (ft_fpath((*env), "OLDPWD=") == ft_tablen((*env)))
	{
		ft_log(TYPE_WARNING, ERROR_ENV);
		return (FALSE);
	}
	if ((old = ft_strsplit((*env)[ft_fpath((*env), "OLDPWD=")], "=")) == NULL)
	{
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (FALSE);
	}
	chdir(old[1]);
	old[1] = ft_chdir_opt_p(old[1], opt);
	if (ft_set_pwd(&(*env), old[1]) == FALSE)
	{
		ft_free_tab(old);
		return (FALSE);
	}
	ft_free_tab(old);
	return (TRUE);
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
		ft_log(TYPE_WARNING, ERROR_ENV);
		return (FALSE);
	}
	if (!str)
		return (ft_chdir_path(ft_getenv(*env, "HOME="), NULL, &(*env), opt));
	if (ft_strcmp(str, "-") == 0)
		return (ft_old(&(*env), opt));
	if (str[0] == '/')
		return (ft_chdir_path(ft_strdup(str), NULL, &(*env), opt));
	if ((tab = ft_strsplit(str, "/")) == NULL)
	{
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (FALSE);
	}
	ft_init_chdir_path(tab, &(*env), opt);
	ft_free_tab(tab);
	return (TRUE);
}
