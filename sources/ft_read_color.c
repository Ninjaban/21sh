/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:32:17 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/09 16:45:59 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_strcopy_color(char **src, char *str, size_t *n)
{
	while (*str)
	{
		(*src)[(*n)++] = *str;
		str = str + 1;
	}
}

void		ft_read_color_main(char *str)
{
	char	*color;

	color = ft_strdup(str);
	color = ft_read_color_first(color);
	color = ft_read_color_hiphen(color);
	ft_putstr_fd(color, 0);
	free(color);
}