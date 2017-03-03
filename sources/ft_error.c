/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:22:04 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 09:24:05 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

void		ft_log(char type, char *log)
{
	char	*str;

	if (type == TYPE_INFO)
		str = " [\e[36mINFO\e[0m]    : ";
	else if (type == TYPE_WARNING)
		str = " [\e[33mWARNING\e[0m] : ";
	else
		str = " [\e[31mERROR\e[0m]   : ";
	ft_putstr_fd(NAME, (type == TYPE_ERROR) ? 2 : 0);
	ft_putstr_fd(str, (type == TYPE_ERROR) ? 2 : 0);
	ft_putendl_fd(log, (type == TYPE_ERROR) ? 2 : 0);
}

void		*ft_error_void(char *error)
{
	ft_putstr_fd(NAME, 2);
	ft_putstr_fd(" [\e[31mERROR\e[0m]   : ", 2);
	ft_putendl_fd(error, 2);
	return (NULL);
}

int			ft_error_int(char *error, int exit)
{
	ft_putstr_fd(NAME, 2);
	ft_putstr_fd(" [\e[31mERROR\e[0m]   : ", 2);
	ft_putendl_fd(error, 2);
	return (exit);
}

void		ft_error(char *error)
{
	ft_putstr_fd(NAME, 2);
	ft_putstr_fd(" [\e[31mERROR\e[0m]   : ", 2);
	ft_putendl_fd(error, 2);
}
