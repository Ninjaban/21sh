/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:14:08 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 15:45:30 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static int	ft_chdir_path(char *path, char **tab, char ****env, char opt)
{
	int		res;

	res = FALSE;
	if (ft_chdir_path_norme(&res, path, tab, env) == FALSE)
		return (FALSE);
	if (ft_access_dir(path) == TRUE)
	{
		chdir(path);
		if (opt == 'P')
			path = ft_chdir_opt_p(path, opt);
		ft_path_trim(&path);
		ft_set_pwd(env[0], env[1], path);
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
		return (ft_error_int("getcdir", FALSE));
	return (TRUE);
}

static int	ft_init_chdir_path(char **tab, char ***env, char ***shvar, char opt)
{
	int		n;
	char	*path;
	char	***env_tab[2];
	int		ret;

	n = -1;
	if ((path = ft_getpwd(*env, *shvar)) == NULL)
		return (ft_error_int(ERROR_ALLOC, FALSE));
	while (tab[++n])
		if ((ft_strcmp(tab[n], ".") != 0) &&
			(ft_chdir_set_path(&(path), tab[n]) == FALSE))
			return (ft_error_int(ERROR_ALLOC, FALSE));
	env_tab[0] = &(*env);
	env_tab[1] = &(*shvar);
	ret = ft_chdir_path(ft_strdup(path), tab, env_tab, opt);
	free(path);
	ft_free_tab(tab);
	return (ret);
}

static int	ft_old(char ***env, char ***shvar, int opt)
{
	char	**old;

	if (ft_fpath((*env), "OLDPWD=") == ft_tablen((*env))
		&& (ft_fpath(*shvar, "OLDPWD=") == ft_tablen(*shvar)))
	{
		ft_log(TYPE_WARNING, ERROR_ENV);
		return (FALSE);
	}
	else if ((old = ft_strsplit((*env)[ft_fpath((*env), "OLDPWD=")],
								"=")) == NULL)
		if ((old = ft_strsplit((*shvar)[ft_fpath((*shvar), "OLDPWD=")],
								"=")) == NULL)
			return (ft_error_int(ERROR_ALLOC, FALSE));
	if (ft_access_dir(old[1]) == TRUE)
		chdir(old[1]);
	old[1] = ft_chdir_opt_p(old[1], opt);
	if (ft_set_pwd(&(*env), &(*shvar), old[1]) == FALSE)
	{
		ft_free_tab(old);
		return (FALSE);
	}
	ft_free_tab(old);
	return (TRUE);
}

int			ft_chdir(char ***env, char ***shvar, char **argv)
{
	char	***e[2];
	char	**tab;
	char	*str;
	char	opt;
	int		n;

	n = ft_chdir_options(argv, &opt);
	str = argv[n];
	if (ft_fpath(*env, "PWD=") == ft_tablen(*env)
		&& ft_fpath(*shvar, "PWD=") == ft_tablen(*shvar))
	{
		ft_log(TYPE_WARNING, ERROR_ENV);
		return (FALSE);
	}
	e[0] = &(*env);
	e[1] = &(*shvar);
	if (!str)
		return (ft_chdir_path(ft_getenv(*env, *shvar, "HOME="), NULL, e, opt));
	if (ft_strcmp(str, "-") == 0)
		return (ft_old(&(*env), &(*shvar), opt));
	if (str[0] == '/')
		return (ft_chdir_path(ft_strdup(str), NULL, e, opt));
	if ((tab = ft_strsplit(str, "/")) == NULL)
		return (ft_error_int(ERROR_ALLOC, FALSE));
	return (ft_init_chdir_path(tab, &(*env), &(*shvar), opt));
}
