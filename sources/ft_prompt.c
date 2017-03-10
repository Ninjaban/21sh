/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 09:04:01 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/10 10:46:00 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static int		ft_path(char **str, char **env)
{
	size_t	n;
	char	**t;
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
			t = ft_strsplit(env[n], "=");
			if (!t)
				return (-1);
			ft_prompt_path(t, bool);
			ft_free_tab(t);
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
				ft_putstr_fd("#", 0);
			else
				ft_putnbr_fd(nbcmd, 0);
			(*str)++;
			return (TRUE);
		}
	}
	return (FALSE);
}

static int		ft_color_prompt(char **str)
{
	char	*tmp;
	size_t	n;

	if (str && *str)
		if (**str == '\033')
		{
			tmp = ft_strstr(*str, "m");
			if (*tmp)
			{
				n = tmp - *str;
				write(0, *str, n);
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
			if (!ft_color_prompt(&str))
				if (!ft_nbcmd(&str, nbcmd))
				{
					if (!(ret = ft_path(&str, env)))
						ft_putchar_fd(*str, 0);
					else if (ret == -1)
						ft_putstr_fd("...", 0);
				}
			str++;
		}
		free(tmp);
	}
}
