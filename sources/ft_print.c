/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 11:42:17 by mrajaona          #+#    #+#             */
/*   Updated: 2017/04/18 11:48:00 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_norme(char **tmp, size_t pos, int inc)
{
	if (!tmp || !(*tmp))
		return ;
	if (!(pos || !inc))
		(*tmp)[ft_strlen(*tmp) - 1] = '\0';
	if (!(pos == 0 && inc == 0))
		ft_putstr_fd(*tmp, 0);
	else
		ft_putstr_fd(" \b", 0);
	free(*tmp);
}
