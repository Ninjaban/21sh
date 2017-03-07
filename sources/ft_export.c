/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:05:48 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/07 14:04:28 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "shell.h"
// #include "error.h"

int	ft_export(char **cmd, char ***env, char ***shvar)
{
	size_t	x;

	x = 0;
	// if (INVALID_OPTION || INVALID_VARNAME || (opt -f && INVAID_FUNCTION))
	// return (FALSE);
	while (cmd[++x])
		ft_setenv(cmd[x], env, shvar, FALSE);
	return (TRUE);
}
