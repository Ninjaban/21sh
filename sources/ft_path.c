/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 18:40:13 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/13 10:08:48 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

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
	int		n;
	int		i;

	n = -1;
	while (env[++n])
		if (ft_strncmp(env[n], "PATH=", 4) == 0)
		{
			i = 0;
			while (env[n][i] != '=')
				env[n][i++] = ':';
			env[n][i] = ':';
			tab = ft_strsplit(env[n], ":");
			ft_verifpath(&tab);
			return (tab);
		}
	return (NULL);
}
