/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir_trim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 11:04:20 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/16 11:10:19 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	ft_trim(char **str)
{
	ft_strdel(str);
	*str = ft_strdup("");
}

static void	ft_path_replace(char **str, char **split)
{
	char	*trim;
	char	*tmp;
	size_t	n;

	trim = ft_strdup("");
	n = 0;
	while (split[n])
	{
		if ((ft_strcmp(split[n], "") != 0))
		{
			tmp = ft_path_join(trim, split[n]);
			ft_strdel(&trim);
			trim = tmp;
		}
		n++;
	}
	if ((ft_strcmp(trim, "") == 0))
		trim = ft_strdup("/");
	ft_strdel(str);
	*str = ft_strdup(trim);
	ft_strdel(&trim);
}

void		ft_path_trim(char **str)
{
	char	**split;
	size_t	n;

	if ((split = ft_strsplit(*str, "/")) == NULL)
		return ;
	n = 0;
	while (split[n])
	{
		if (ft_strcmp(split[n], ".") == 0)
			ft_trim(&(split[n]));
		else if (ft_strcmp(split[n], "..") == 0)
		{
			ft_trim(&(split[n]));
			if (n > 0)
				n--;
			while (n > 0 && (ft_strcmp(split[n], "") == 0))
				n--;
			ft_trim(&(split[n]));
		}
		n++;
	}
	ft_path_replace(str, split);
	ft_free_tab(split);
}
