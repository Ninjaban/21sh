/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 10:20:56 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/09 13:14:49 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static size_t	ft_find_path(char **env, char *str)
{
	size_t		n;

	n = 0;
	while (env[n])
		if (ft_strncmp(env[n++], str, ft_strlen(str) - 1) == 0)
			return (n - 1);
	return (n);
}

static void		ft_del_line(char ***env, size_t i)
{
	char		**tab;
	size_t		n;
	size_t		j;

	j = 0;
	n = 0;
	if ((tab = malloc(sizeof(char *) * ft_tablen(*env))) == NULL)
		return ;
	while ((*env)[n])
	{
		if (n != i)
			tab[j++] = ft_strdup((*env)[n]);
		n = n + 1;
	}
	tab[j] = NULL;
	ft_free_tab(*env);
	(*env) = tab;
	ft_putendl("L'environement a été modifiée.");
}

static void		ft_init_pwd(char ***env)
{
	char		*path;
	char		*tmp;

	if ((tmp = ft_getenv((*env), "HOME")) == NULL)
		return ;
	path = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (path)
		ft_setenv(path, &(*env), TRUE);
}

void			ft_unsetenv(char ***env, char *str)
{
	size_t		n;

	if ((n = ft_find_path(*env, str)) == ft_tablen(*env))
		ft_putendl("Variable non trouvé.");
	else if (ft_strcmp(str, "PWD") == 0)
		ft_init_pwd(&(*env));
	else if (ft_strcmp(str, "HOME") != 0)
		ft_del_line(&(*env), n);
}
