/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:41:52 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 11:20:45 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static void	*ft_gestion_cmd(t_cmd *cmd)
{
	if (cmd)
		return (NULL);
	return (NULL);
}

void		*ft_gestion_error(t_cmd **cmds)
{
	size_t	n;
	char	*tmp;

	n = 0;
	while (cmds[n])
		if ((tmp = (char *)ft_gestion_cmd(cmds[n++])) != NULL)
			return (tmp);
	return (NULL);
}
