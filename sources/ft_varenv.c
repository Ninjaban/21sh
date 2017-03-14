/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 08:30:52 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/12 09:54:02 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

static char	*ft_getvalue(char *str, char **env)
{
	char	*value;

	value = ft_getenv(env, str);
	return (value);
}

static char	*ft_checkvalue(char *str, t_sys *sys)
{
	char	*value;
	char	*key;
	char	c;
	int		n;

	n = 0;
	while (str[n] && str[n] != ' ' && str[n] != '\t')
		n = n + 1;
	c = str[n];
	str[n] = '\0';
	key = ft_strjoin(str, "=");
	if (ft_fpath(sys->env, key) != ft_tablen(sys->env))
		value = ft_getvalue(key, sys->env);
	else
		value = ft_getvalue(key, sys->shvar);
	free(key);
	str[n] = c;
	return (value);
}

static char	*ft_init_join(char *new, char *str)
{
	char	*tmp;

	if (!str)
		return (new);
	if (!new)
		return (str);
	tmp = ft_strjoin(new, str);
	free(new);
	free(str);
	return (tmp);
}

static char	*ft_init_new(char *new, char *tmp, char *cpy, t_sys *sys)
{
	char	*value;

	*tmp = '\0';
	new = ft_init_join(new, ft_strdup(cpy));
	*tmp = '$';
	if ((value = ft_checkvalue(++tmp, sys)) != NULL)
		new = ft_init_join(new, value);
	return (new);
}

char		*ft_varenv(char *str, t_sys *sys, char change)
{
	char	*cpy;
	char	*tmp;
	char	*new;

	new = NULL;
	cpy = str;
	tmp = str;
	while (*tmp)
	{
		if (*tmp == '\'')
			change = (change == TRUE) ? FALSE : TRUE;
		if (*tmp == '$' && change == TRUE)
		{
			new = ft_init_new(new, tmp, cpy, sys);
			while (*tmp && *tmp != ' ' && *tmp != '\t')
				tmp++;
			cpy = tmp;
		}
		else
			tmp++;
	}
	return (ft_init_join(new, ft_strdup(cpy)));
}
