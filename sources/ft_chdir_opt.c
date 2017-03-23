/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:02:57 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/23 14:37:18 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

char		*ft_chdir_opt_p(char *path, char opt)
{
	char	*tmp;
	size_t	bufsize;

	bufsize = 4096;
	tmp = NULL;
	if (opt == 'P')
	{
		free(path);
		if ((tmp = getcwd(tmp, bufsize)) != NULL)
		{
			path = ft_strdup(tmp);
			free(tmp);
		}
		chdir(path);
	}
	return (path);
}

static char	ft_chdir_opt(char *arg)
{
	char	opt;
	int		n;

	opt = 'L';
	n = 1;
	while (arg[n])
	{
		if (arg[n] == 'L' || arg[n] == 'P')
			opt = arg[n];
		else
			return (-1);
		n++;
	}
	return (opt);
}

int			ft_chdir_options(char **argv, char *opt)
{
	int	n;

	*opt = 'L';
	n = 1;
	while (argv[n] && argv[n][0] == '-' && ft_strcmp(argv[n], "-") != 0)
	{
		if ((*opt = ft_chdir_opt(argv[n])) < 0)
		{
			ft_log(TYPE_WARNING, ERROR_OPTION);
			return (FALSE);
		}
		n++;
	}
	return (n);
}
