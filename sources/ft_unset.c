/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:42:03 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/07 14:05:51 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static size_t	ft_find_path(char **env, char *str)
{
	size_t		n;

	n = 0;
	while (env[n])
		if (ft_strncmp(env[n++], str, ft_strlen(str) - 1) == 0)
			return (n - 1);
	return (n);
}

static int		ft_del_line(char ***env, size_t i)
{
	char		**tab;
	size_t		n;
	size_t		j;

	j = 0;
	n = 0;
	if ((tab = malloc(sizeof(char *) * ft_tablen(*env))) == NULL)
		return (FALSE);
	while ((*env)[n])
	{
		if (n != i)
			tab[j++] = ft_strdup((*env)[n]);
		n = n + 1;
	}
	tab[j] = NULL;
	ft_free_tab(*env);
	(*env) = tab;
	return (TRUE);
}

static void		ft_init_pwd(char ***env)
{
	char		*path;
	char		*tmp;

	if ((tmp = ft_getenv((*env), "HOME=")) == NULL)
		return ;
	path = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (path)
		ft_setenv(path, &(*env), NULL, TRUE);
}

int				ft_unset(char ***env, char ***shvar, char **str)
{
	size_t		n;
	size_t		m;
	size_t		x;
	int			ret;

	ret = TRUE;
	if (!str)
		return (TRUE);
	x = 0;
	while (str[x])
	{
		n = ft_find_path(*env, str[x]);
		m = ft_find_path(*shvar, str[x]);
		if (n == ft_tablen(*env) && m == ft_tablen(*shvar))
		{
			ft_log(TYPE_ERROR, ERROR_VNOTFOUND);
			ret = FALSE;
		}
		else if (ft_strcmp(str[x], "PWD") == 0)
			ft_init_pwd(&(*env));
		else if (ft_strcmp(str[x], "HOME") != 0)
			if (ft_del_line((n == ft_tablen(*env) ? &(*shvar) : &(*env)),
							(n == ft_tablen(*env) ? m : n)) == FALSE)
				return (FALSE);
		x++;
	}
	return (ret);
}
