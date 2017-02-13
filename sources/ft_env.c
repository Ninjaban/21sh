/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 22:02:39 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 22:04:17 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static char	**ft_tabcpy(char **t)
{
	char	**cpy;
	int		n;

	n = 0;
	if ((cpy = malloc(sizeof(char *) * (ft_tablen(t) + 1))) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (NULL);
	}
	while (t[n])
		cpy[n++] = NULL;
	cpy[n] = NULL;
	n = -1;
	while (t[++n])
		if ((cpy[n] = ft_strdup(t[n])) == NULL)
		{
			ft_error(ERROR_ALLOC);
			ft_free_tab(cpy);
			return (NULL);
		}
	return (cpy);
}

static void	ft_env_set(char **argv, char ***tab, size_t *n)
{
	while (argv[*n] && ft_strchr(argv[*n], '=') != NULL)
		ft_setenv(argv[(*n)++], &(*tab), FALSE);
}

static void	ft_env_print(char **tab)
{
	size_t	n;

	n = 0;
	if (tab)
		while (tab[n])
			ft_putendl(tab[n++]);
}

static int	ft_env_launch(char **argv, char **tab, size_t n)
{
	pid_t	child;

	if ((child = fork()) == -1)
	{
		ft_error(ERROR_FORK);
		return (FALSE);
	}
	else if (child == 0)
	{
		execve(argv[n], argv + n, tab);
		ft_error(ERROR_EXEC);
		exit(1);
	}
	return (TRUE);
}

int			ft_env(char **argv, char **env)
{
	size_t	n;
	char	**tab;

	n = (ft_strcmp(argv[1], "-i") == 0) ? 2 : 1;
	tab = (ft_strcmp(argv[1], "-i") == 0) ?
			ft_strsplit(" ", " ") : ft_tabcpy(env);
	ft_env_set(argv, &tab, &n);
	if (argv[n] == NULL)
		ft_env_print(tab);
	else if (ft_env_launch(argv, tab, n) == FALSE)
		return (FALSE);
	ft_free_tab(tab);
	return (TRUE);
}
