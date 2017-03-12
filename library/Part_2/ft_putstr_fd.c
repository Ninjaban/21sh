/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:47:46 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/03 16:35:59 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_esc.h"

void	ft_putstr_fd(char *str, int fd)
{
	char	*tmp;

	if (str != NULL)
	{
		tmp = ft_eval(str);
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
	}
}
