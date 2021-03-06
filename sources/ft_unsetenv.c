/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 10:20:56 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 13:30:48 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

int				ft_unsetenv(char ***env, char *str)
{
	size_t		n;

	if ((n = ft_find_path(*env, str)) == ft_tablen(*env))
		return (ft_error_int(ERROR_VNOTFOUND, FALSE));
	else if (ft_strcmp(str, "HOME") != 0)
		if (ft_del_line(&(*env), n) == FALSE)
			return (FALSE);
	return (TRUE);
}
