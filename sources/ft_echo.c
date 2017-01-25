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

void		ft_echo(char **argv)
{
	size_t	n;

	n = 1;
	while (argv[n])
	{
		ft_putstr(argv[n]);
		if (argv[++n])
			ft_putstr(" ");
	}
	ft_putstr("\n");
}
