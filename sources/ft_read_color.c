/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:32:17 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/17 13:04:04 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		ft_check_sep(char *str)
{
	if (str[0] == ';' || str[0] == '|' || str[0] == '>' || str[0] == '<' ||
			ft_strncmp(str, "||", 1) == 0 || ft_strncmp(str, "&&", 1) == 0 ||
			ft_strncmp(str, ">>", 1) == 0 || ft_strncmp(str, "<<", 1) == 0)
		return (TRUE);
	return (FALSE);
}

void		ft_strcopy_color(char **src, char *str, size_t *n)
{
	while (*str)
	{
		(*src)[(*n)++] = *str;
		str = str + 1;
	}
}

void		ft_read_color_main(char *str, size_t pos, size_t limit)
{
	char	*color;

	color = ft_strdup(str);
	color = ft_read_color_inhibitor(color);
	color = ft_read_color_first(color);
	color = ft_read_color_fd(color);
	color = ft_read_color_hyphen(color);
	color = ft_read_color_redirect(color);
	ft_putstr_limit(color, pos, limit);
	free(color);
}
