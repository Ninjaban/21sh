/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:42:03 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/09 13:21:25 by mrajaona         ###   ########.fr       */
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

/*
  If -v is specified, name refers to a variable name. (default)
  Read-only variables cannot be unset.

  If -f is specified, name refers to a function.
  The shell shall unset the function definition.
*/

static int		ft_unset_opt(size_t *x, char *opt, char **cmd)
{
	size_t	n;

	while (cmd[++(*x)] && cmd[*x][0] == '-')
	{
		n = 0;
		while (cmd[*x][++n])
		{
			if (cmd[*x][n] == 'f')
				*opt = 'f';
			else if (cmd[*x][n] == 'v')
				*opt = 'v';
			else
				return (ft_error_int(ERROR_OPTION, FALSE));
		}
	}
	return (TRUE);
}

static int		ft_unset_var(char ***env, char ***shvar, char *str)
{
	size_t		n;
	size_t		m;

	n = ft_find_path(*env, str);
	m = ft_find_path(*shvar, str);
	if (n == ft_tablen(*env) && m == ft_tablen(*shvar))
		return (ft_error_int(ERROR_VNOTFOUND, FALSE));
	else if (ft_strcmp(str, "PWD") == 0)
		ft_init_pwd(&(*env));
	else if (ft_strcmp(str, "HOME") != 0)
		if (ft_del_line((n == ft_tablen(*env) ? &(*shvar) : &(*env)),
						(n == ft_tablen(*env) ? m : n)) == FALSE)
			return (FALSE);
	return (TRUE);
}

int				ft_unset(char ***env, char ***shvar, char **cmd)
{
	size_t		x;
	int			ret;
	char		opt;

	ret = TRUE;
	if (!(cmd[1]))
		return (TRUE);
	x = 0;
	opt = 'v';
	if (ft_unset_opt(&x, &opt, cmd) != TRUE)
		return (FALSE);
	while (cmd[x])
	{
		if (opt == 'v')
		{
			if (ft_unset_var(env, shvar, cmd[x]) != TRUE && ret == TRUE)
				ret = FALSE;
		}
		else
			ft_log(TYPE_WARNING, "Option -f non supportée.");
		x++;
	}
	return (ret);
}
