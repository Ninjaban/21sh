/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:36:28 by mrajaona          #+#    #+#             */
/*   Updated: 2016/12/19 14:13:27 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
	else
		write(fd, "(null)", 6);
	write(fd, "\n", 1);
}
