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

void		ft_error(char *error)
{
	ft_putstr_fd(NAME, 2);
	ft_putstr_fd(" : ", 2);
	ft_putendl_fd(error, 2);
}
