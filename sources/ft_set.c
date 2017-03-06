/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:16:47 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/06 12:19:46 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static size_t	ft_find_path(char **shvar, char *str)
{
	size_t		n;

	n = 0;
	if (shvar)
		while (shvar[n])
			if (ft_strncmp(shvar[n++], str, ft_strlen(str) - 1) == 0)
				return (n - 1);
	return (n);
}

static void		ft_change_var(char ***shvar, char *str, size_t n)
{
	char		*tmp;

	if ((tmp = ft_strdup(str)) == NULL)
		return (ft_error(ERROR_ALLOC));
	free((*shvar)[n]);
	(*shvar)[n] = tmp;
}

static void		ft_add_var(char ***shvar, char *str, size_t n)
{
	char	**tab;
	int		i;

	if ((tab = malloc(sizeof(char *) * (n + 2))) == NULL)
		return (ft_error(ERROR_ALLOC));
	i = -1;
	while ((*shvar)[++i])
		tab[i] = ft_strdup((*shvar)[i]);
	tab[i++] = ft_strdup(str);
	tab[i] = NULL;
	ft_free_tab(*shvar);
	*shvar = tab;
}

static int	ft_shvar_print(char **env, char **shvar)
{
	size_t	n;

	n = 0;
	if (env)
		while (env[n])
			ft_putendl(env[n++]);
	n = 0;
	if (shvar)
		while (shvar[n])
			ft_putendl(shvar[n++]);
	return (TRUE);
}

int				ft_set(char *str, char ***env, char ***shvar, int bool)
{
	char	**tab;
	size_t	n;

	if (str == NULL)
		return (ft_shvar_print(*env, *shvar));
	if ((tab = ft_strsplit(str, "=")) == NULL)
	{
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (FALSE);
	}
	if (ft_tablen(tab) != 2)
	{
		ft_free_tab(tab);
		ft_log(TYPE_ERROR, ERROR_SYNTAX);
		return (FALSE);
	}
	if ((n = ft_find_path(*shvar, tab[0])) != ft_tablen(*shvar))
		ft_change_var(&(*shvar), str, n);
	else
		ft_add_var(&(*shvar), str, n);
	ft_free_tab(tab);
	if (bool == TRUE)
		free(str);
	return (TRUE);
}
