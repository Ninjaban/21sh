/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:42:03 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/17 10:43:52 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

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

static int		ft_unset_ft(char ***ftvar, char *str)
{
	size_t		n;

	n = ft_find_path(*ftvar, str);
	if (n == ft_tablen(*ftvar))
		return (ft_error_int(ERROR_VNOTFOUND, FALSE));
	else if (ft_del_line(&(*ftvar), n) == FALSE)
		return (FALSE);
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

int				ft_unset(char ***env, char ***shvar, char ***ftvar, char **cmd)
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
		if (((opt == 'v' && ft_unset_var(env, shvar, cmd[x]) != TRUE)
			|| (opt == 'f' && ft_unset_ft(ftvar, cmd[x]) != TRUE))
			&& ret == TRUE)
			ret = FALSE;
		x++;
	}
	return (ret);
}
