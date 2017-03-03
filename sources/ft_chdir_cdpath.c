/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir_cdpath.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 13:44:22 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/02 13:57:16 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static void	ft_verifpath(char ***path)
{
	int		n;

	n = 0;
	while ((*path)[n])
	{
		if ((*path)[n][ft_strlen((*path)[n]) - 1] == '/')
			(*path)[n][ft_strlen((*path)[n]) - 1] = '\0';
		n = n + 1;
	}
}

char		**ft_getcdpath(char **env)
{
	char	**tab;
	char	*tmp;
	int		n;
	int		i;

	n = -1;
	while (env[++n])
		if (ft_strncmp(env[n], "CDPATH=", 6) == 0)
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

int			ft_chdir_cdpath(char **path, char **cdpath, char **tab)
{
	int	m;
	int	n;

	m = -1;
	while (cdpath[++m] && access(*path, F_OK) != 0)
	{
		free(*path);
		n = -1;
		while (tab[++n])
			if ((ft_strcmp(tab[n], ".") != 0) &&
				(ft_chdir_set_path(&(cdpath[m]), tab[n]) == FALSE))
			{
				ft_log(TYPE_ERROR, ERROR_ALLOC);
				return (FALSE);
			}
		*path = ft_strdup(cdpath[m]);
	}
	return (TRUE);
}
