/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 18:40:13 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 13:15:48 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

char		*ft_path_join(char *src, char *str)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(src, "/");
	path = ft_strjoin(tmp, str);
	free(tmp);
	return (path);
}

static void	ft_verifpath(char ***path)
{
	char	*tmp;
	int		n;

	n = 0;
	while ((*path)[n])
	{
		if ((*path)[n][ft_strlen((*path)[n]) - 1] != '/')
		{
			tmp = ft_strjoin((*path)[n], "/");
			free((*path)[n]);
			(*path)[n] = tmp;
		}
		n = n + 1;
	}
}

char		**ft_getpath(char **env)
{
	char	**tab;
	char	*tmp;
	int		n;
	int		i;

	n = -1;
	while (env[++n])
		if (ft_strncmp(env[n], "PATH=", 4) == 0)
		{
			i = 0;
			if ((tmp = ft_strdup(env[n])) == NULL)
				return (NULL);
			while (tmp[i] != '=')
				tmp[i++] = ':';
			tmp[i] = ':';
			tab = ft_strsplit(tmp, ":");
			free(tmp);
			ft_verifpath(&tab);
			return (tab);
		}
	return (NULL);
}
