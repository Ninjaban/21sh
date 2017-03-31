/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir_cdpath.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 13:44:22 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 15:45:51 by mrajaona         ###   ########.fr       */
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

static int	ft_chdir_cdpath(char **path, char **cdpath, char **tab)
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
				free(*path);
				return (ft_error_int(ERROR_ALLOC, FALSE));
			}
		*path = ft_strdup(cdpath[m]);
	}
	return (TRUE);
}

int			ft_chdir_path_norme(int *res, char *path, char **tab, char ****env)
{
	char	**cdpath;

	if (!path)
		return (FALSE);
	if ((cdpath = ft_getcdpath((*env)[0])) == NULL)
		cdpath = ft_getcdpath((*env)[1]);
	if (access(path, F_OK) != 0 && cdpath)
		if ((*res = ft_chdir_cdpath(&path, cdpath, tab)) == FALSE)
		{
			ft_free_tab(cdpath);
			return (FALSE);
		}
	if (cdpath)
		ft_free_tab(cdpath);
	return (TRUE);
}
