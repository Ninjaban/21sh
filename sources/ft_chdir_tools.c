/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:53:39 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/13 10:09:52 by jcarra           ###   ########.fr       */
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

char		*ft_path_join(char *src, char *str)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(src, "/");
	path = ft_strjoin(tmp, str);
	free(tmp);
	return (path);
}

int			ft_set_pwd(char ***env, char *str)
{
	char	**pwd;

	if ((pwd = ft_strsplit((*env)[ft_fpath((*env), "PWD")], "=")) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	ft_setenv(ft_cvar("OLDPWD", pwd[1]), &(*env), TRUE);
	ft_setenv(ft_cvar("PWD", str), &(*env), TRUE);
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

char		*ft_getenv(char **env, char *name)
{
	char	**tab;
	char	*str;

	if (ft_fpath(env, name) == ft_tablen(env))
		return (NULL);
	if ((tab = ft_strsplit(env[ft_fpath(env, name)], "=")) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (NULL);
	}
	if (!tab[0] || !tab[1])
		return (NULL);
	str = ft_strdup(tab[1]);
	ft_free_tab(tab);
	return (str);
}
