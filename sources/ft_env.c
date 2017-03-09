/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 22:02:39 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/09 11:04:36 by mrajaona         ###   ########.fr       */
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
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (NULL);
	}
	while (t[n])
		cpy[n++] = NULL;
	cpy[n] = NULL;
	n = -1;
	while (t[++n])
		if ((cpy[n] = ft_strdup(t[n])) == NULL)
		{
			ft_log(TYPE_ERROR, ERROR_ALLOC);
			ft_free_tab(cpy);
			return (NULL);
		}
	return (cpy);
}

static void	ft_env_set(char **argv, char ***tab, char ***shvar, size_t *n)
{
	while (argv[*n] && ft_strchr(argv[*n], '=') != NULL)
		ft_setenv(argv[(*n)++], &(*tab), shvar, FALSE);
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
	int		status;

	if ((child = fork()) == -1)
	{
		ft_log(TYPE_ERROR, ERROR_FORK);
		return (FALSE);
	}
	else if (child == 0)
	{
		execve(argv[n], argv + n, tab);
		ft_log(TYPE_ERROR, ERROR_EXEC);
		exit(1);
	}
	else if (child > 0)
	{
		if (waitpid(child, &status, 0) > 0)
		{
			if (WIFEXITED(status) && !WEXITSTATUS(status))
				return (TRUE);
		}
		else
			return (FALSE);
	}
	return (TRUE);
}

int			ft_env(char **argv, char **env, char ***shvar)
{
	size_t	n;
	char	**tab;

	n = (ft_strcmp(argv[1], "-i") == 0) ? 2 : 1;
	tab = (ft_strcmp(argv[1], "-i") == 0) ?
		ft_strsplit(" ", " ") : ft_tabcpy(env);
	ft_env_set(argv, &tab, shvar, &n);
	if (argv[n] == NULL)
		ft_env_print(tab);
	else if (ft_env_launch(argv, tab, n) == FALSE)
		return (FALSE);
	ft_free_tab(tab);
	return (TRUE);
}
