/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:47:46 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 11:06:58 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_esc.h"

void	ft_putendl(char *str)
{
	char	*tmp;

	if (str != NULL)
	{
		tmp = ft_eval(str);
		write(1, tmp, ft_strlen(tmp));
		free(tmp);
	}
	else
		write(1, "(null)", ft_strlen("(null)"));
	ft_putchar('\n');
}
