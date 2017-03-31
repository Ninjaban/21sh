/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:53:39 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 14:30:05 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static char	*ft_cvar(char *name, char *value)
{
	char	*tmp;
	char	*var;

	if ((tmp = ft_strjoin("=", value)) == NULL)
		return (NULL);
	if ((var = ft_strjoin(name, tmp)) == NULL)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (var);
}

int			ft_set_pwd(char ***env, char ***shvar, char *str)
{
	char	**pwd;

	if ((pwd = ft_strsplit((*env)[ft_fpath((*env), "PWD=")], "=")) == NULL)
		if ((pwd = ft_strsplit((*shvar)[ft_fpath((*shvar), "PWD=")],
								"=")) == NULL)
		{
			ft_log(TYPE_ERROR, ERROR_ALLOC);
			return (FALSE);
		}
	ft_setenv(ft_cvar("OLDPWD", pwd[1]), &(*env), &(*shvar), TRUE);
	ft_setenv(ft_cvar("PWD", str), &(*env), &(*shvar), TRUE);
	ft_free_tab(pwd);
	return (TRUE);
}

size_t		ft_fpath(char **env, char *str)
{
	size_t		n;

	n = 0;
	while (env[n])
		if (ft_strncmp(env[n++], str, ft_strlen(str) - 1) == 0)
			return (n - 1);
	return (n);
}

static char	*ft_getenv_sub(char **env, char *name)
{
	char	**t;
	char	*str;

	if (ft_fpath(env, name) == ft_tablen(env))
		return (NULL);
	if ((t = ft_strsplit(env[ft_fpath(env, name)], "=")) == NULL)
	{
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (NULL);
	}
	if (!t[0] || !t[1])
		return (NULL);
	str = ft_strdup(t[1]);
	ft_free_tab(t);
	return (str);
}

char		*ft_getenv(char **env, char **shvar, char *name)
{
	char	*str;

	if ((str = ft_getenv_sub(env, name)) == NULL)
		str = ft_getenv_sub(shvar, name);
	return (str);
}
