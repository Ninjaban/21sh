/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 18:54:52 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/12 08:34:29 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static char		*ft_trypath(char *name, char **path)
{
	char		*tmp;
	int			n;

	n = 0;
	while (path[n])
	{
		tmp = ft_strjoin(path[n++], name);
		if (tmp && access(tmp, F_OK) == 0)
		{
			if (access(tmp, X_OK) == 0)
				return (tmp);
			else
			{
				ft_error(ERROR_PERMS);
				return (NULL);
			}
		}
	}
	ft_error(ERROR_NOTFOUND);
	return (NULL);
}

char			*ft_access(char *name, char **env)
{
	char		**path;
	char		*tmp;

	if (access(name, F_OK) == 0)
	{
		if (access(name, X_OK) != 0)
		{
			ft_error(ERROR_PERMS);
			return (NULL);
		}
		if ((tmp = ft_strdup(name)) == NULL)
			ft_error(ERROR_ALLOC);
		return (tmp);
	}
	if ((path = ft_getpath(env)) == NULL)
	{
		ft_error(ERROR_ENV);
		return (NULL);
	}
	tmp = ft_trypath(name, path);
	free(path);
	return (tmp);
}

int				ft_access_dir(char *path)
{
	struct stat	*buf;

	if (path && access(path, F_OK) != 0)
	{
		ft_error(ERROR_DNOTFOUND);
		return (-1);
	}
	if ((buf = malloc(sizeof(struct stat))) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (-1);
	}
	if (stat(path, buf) == -1)
	{
		free(buf);
		return (-1);
	}
	if (S_ISDIR(buf->st_mode))
	{
		free(buf);
		return (TRUE);
	}
	return (FALSE);
}
