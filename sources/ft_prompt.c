/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 09:04:01 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/13 10:10:31 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static size_t	ft_find_path(char **env, char *str)
{
	size_t		n;

	n = 0;
	while (env[n])
		if (ft_strncmp(env[n++], str, ft_strlen(str) - 1) == 0)
			return (n - 1);
	return (n);
}

static int		ft_path(char **str, char **env)
{
	size_t	n;
	char	**tab;
	char	bool;

	if (str && *str)
	{
		bool = (ft_strncmp(*str, "!w", 1) == 0) ? FALSE : -1;
		bool = (bool != FALSE && ft_strncmp(*str, "!W", 1) == 0) ? TRUE : bool;
		if (bool != -1)
		{
			(*str)++;
			if (!env)
				return (-1);
			n = ft_find_path(env, "PWD");
			if (!env[n])
				return (-1);
			tab = ft_strsplit(env[n], "=");
			if (!tab)
				return (-1);
			ft_prompt_path(tab, bool);
			ft_free_tab(tab);
			return (TRUE);
		}
	}
	return (FALSE);
}

static int		ft_nbcmd(char **str, size_t nbcmd)
{
	if (str && *str)
	{
		if (ft_strncmp(*str, "!#", 1) == 0)
		{
			if (nbcmd == 0)
				ft_putstr("#");
			else
				ft_putnbr(nbcmd);
			(*str)++;
			return (TRUE);
		}
	}
	return (FALSE);
}

static int		ft_color(char **str)
{
	char	*tmp;
	size_t	n;

	tmp = NULL;
	if (str && *str)
		if (**str == '\033')
		{
			tmp = ft_strstr(*str, "m");
			if (*tmp)
			{
				n = tmp - *str;
				write(1, *str, n);
				while (*str != tmp - 1)
					(*str)++;
				return (TRUE);
			}
		}
	return (FALSE);
}

void			ft_affprompt(size_t nbcmd, char **env)
{
	char	*str;
	char	*tmp;
	int		ret;

	str = ft_strdup(PROMPT);
	tmp = str;
	if (str)
	{
		while (*str)
		{
			if (!ft_color(&str))
				if (!ft_nbcmd(&str, nbcmd))
				{
					if (!(ret = ft_path(&str, env)))
						ft_putchar(*str);
					else if (ret == -1)
						ft_putstr("...");
				}
			str++;
		}
		free(tmp);
	}
}
