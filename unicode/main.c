/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 14:49:11 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/07 15:29:21 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_esc.h"

int	main(int ac, char **av)
{
	char	*str;

	str = NULL;
	if (ac == 2)
		str = ft_eval(av[1]);
	ft_putendl(str);
	if (str)
		free(str);
	return (0);
}
