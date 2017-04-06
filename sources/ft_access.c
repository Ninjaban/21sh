/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 18:54:52 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 12:54:13 by mrajaona         ###   ########.fr       */
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
				free(tmp);
				ft_log(TYPE_WARNING, ERROR_PERMS);
				return (NULL);
			}
		}
		free(tmp);
	}
	ft_log(TYPE_WARNING, ERROR_NOTFOUND);
	ft_cmd_nfound(name);
	return (NULL);
}

char			*ft_access(char *name, char **env, char **shvar)
{
	char		**path;
	char		*tmp;

	if ((ft_strncmp(name, "/", 0) == 0 || ft_strncmp(name, "./", 1) == 0) &&
			access(name, F_OK) == 0)
	{
		if (access(name, X_OK) != 0)
		{
			ft_log(TYPE_WARNING, ERROR_PERMS);
			return (NULL);
		}
		if ((tmp = ft_strdup(name)) == NULL)
			ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (tmp);
	}
	if ((path = ft_getpath(env)) == NULL)
		if ((path = ft_getpath(shvar)) == NULL)
		{
			ft_log(TYPE_WARNING, ERROR_ENV);
			ft_cmd_nfound(name);
			return (NULL);
		}
	tmp = ft_trypath(name, path);
	ft_free_tab(path);
	return (tmp);
}

static char		ft_free_int(struct stat *buf, char exit)
{
	free(buf);
	return (exit);
}

int				ft_access_dir(char *path)
{
	struct stat	*buf;

	if (path && access(path, F_OK) != 0)
	{
		ft_log(TYPE_WARNING, ERROR_DNOTFOUND);
		return (-1);
	}
	if (path && access(path, X_OK) != 0)
	{
		ft_log(TYPE_WARNING, ERROR_PERMS);
		return (-1);
	}
	if ((buf = malloc(sizeof(struct stat))) == NULL)
		return (ft_error_int(ERROR_ALLOC, -1));
	if (stat(path, buf) == -1)
		return (ft_free_int(buf, -1));
	if (S_ISDIR(buf->st_mode))
		return (ft_free_int(buf, TRUE));
	ft_log(TYPE_WARNING, ERROR_NOTDIR);
	return (FALSE);
}
