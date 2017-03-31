/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 08:30:52 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 13:33:53 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

char		*ft_getpwd(char **env, char **shvar)
{
	char	*str;

	str = NULL;
	if ((str = ft_strnew(4096)) == NULL || (getcwd(str, 4096) == NULL))
	{
		if (str)
			free(str);
		str = ft_getenv(env, shvar, "PWD=");
	}
	return (str);
}

static char	*ft_checkvalue(char *str, t_sys *sys)
{
	char	*value;
	char	*key;
	char	c;
	int		n;

	n = 0;
	while (str[n] && str[n] != ' ' && str[n] != '\t' &&
			str[n] != '\"' && str[n] != '$')
		n = n + 1;
	c = str[n];
	str[n] = '\0';
	key = ft_strjoin(str, "=");
	value = ft_getenv(sys->env, sys->shvar, key);
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
			++tmp;
			while (*tmp && *tmp != ' ' && *tmp != '\t' &&
					*tmp != '\"' && *tmp != '$')
				tmp++;
			cpy = tmp;
		}
		else
			tmp++;
	}
	return (ft_init_join(new, ft_strdup(cpy)));
}
