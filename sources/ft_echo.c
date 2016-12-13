/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 21:13:50 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/08 15:27:54 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

void		ft_echo(char **argv, char **env)
{
	size_t	n;
	char	*tmp;

	n = 1;
	while (argv[n])
	{
		if (argv[n][0] == '$')
		{
			tmp = ft_getenv(env, argv[n] + 1);
			if (tmp)
				ft_putstr(tmp);
			free(tmp);
		}
		else
			ft_putstr(argv[n]);
		if (argv[++n])
			ft_putstr(" ");
	}
	ft_putstr("\n");
}
