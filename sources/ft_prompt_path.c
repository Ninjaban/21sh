/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:45:58 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/16 14:42:48 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

void		ft_prompt_path(char **t, char bool)
{
	size_t	n;
	char	**dir;

	if (bool == FALSE)
		ft_putstr_fd(t[1], 0);
	else
	{
		dir = ft_strsplit(t[1], "/");
		n = 0;
		if (!dir)
		{
			ft_putstr_fd("...", 0);
			return ;
		}
		while (dir[n])
			n = n + 1;
		ft_putstr_fd((n > 0) ? dir[n - 1] : "/", 0);
		ft_free_tab(dir);
	}
}
