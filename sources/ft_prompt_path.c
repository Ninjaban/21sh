/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:45:58 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/16 14:42:48 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static char	*ft_prompt_path(char *t, char bool)
{
	size_t	n;
	char	**dir;
	char	*ret;

	if (bool == FALSE)
		return (ft_strdup(t));
	else
	{
		dir = ft_strsplit(t, "/");
		n = 0;
		if (!dir)
			return (ft_strdup("..."));
		while (dir[n])
			n = n + 1;
		ret = ft_strdup((n > 0) ? dir[n - 1] : "/");
		ft_free_tab(dir);
		return (ret);
	}
}

char		*ft_path(char *str, char **env, size_t *n)
{
	char	*t;
	char	*ret;
	char	bool;

	if (str && *str)
	{
		bool = (ft_strncmp(str, "!w", 1) == 0) ? FALSE : (char)-1;
		bool = (bool != FALSE && ft_strncmp(str, "!W", 1) == 0) ? TRUE : bool;
		if (bool != -1)
		{
			*n = *n + 2;
			if (!env)
				return (ft_strdup("..."));
			if (!(t = ft_getenv(env, "PWD=")))
				return (ft_strdup("..."));
			ret = ft_prompt_path(t, bool);
			free(t);
			return (ret);
		}
	}
	return (FALSE);
}
