/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:45:58 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/13 10:11:05 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

void		ft_prompt_path(char **tab, char bool)
{
	size_t	n;
	char	**dir;

	if (bool == FALSE)
		ft_putstr(tab[1]);
	else
	{
		dir = ft_strsplit(tab[1], "/");
		n = 0;
		if (!dir)
		{
			ft_putstr("...");
			return ;
		}
		while (dir[n])
			n = n + 1;
		ft_putstr((n > 0) ? dir[n - 1] : "/");
		ft_free_tab(dir);
	}
}
