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
	char	*tmp;
	char	c;
	int		n;

	n = 0;
	while (ft_isalnum(str[n]) == 1)
		n = n + 1;
	c = str[n];
	str[n] = '\0';
	tmp = ft_strjoin(str, "=");
	value = ft_getenv(env, tmp);
	free(tmp);
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

char		*ft_varenv(char *str, char **env, char change)
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
			*tmp = '\0';
			new = ft_init_join(new, ft_strdup(cpy));
			*tmp = '$';
			new = ft_init_join(new, ft_getvalue(++tmp, env));
			while (ft_isalnum(*tmp) == 1)
				tmp++;
			cpy = tmp;
		}
		else
			tmp++;
	}
	return (ft_init_join(new, ft_strdup(cpy)));
}
