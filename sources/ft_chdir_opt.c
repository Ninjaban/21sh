/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:02:57 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/02 14:32:02 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

char		*ft_chdir_opt_p(char *path, char opt)
{
	char	*tmp;
	size_t	bufsize;

	tmp = NULL;
	bufsize = 4096;
	if (opt == 'P')
	{
		free(path);
		tmp = getcwd(tmp, bufsize);
		path = tmp;
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
