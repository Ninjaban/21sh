/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 09:04:01 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/10 10:46:00 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static char		ft_strjoinr(char **src, char *str)
{
	char	*tmp;

	if (!(*src))
	{
		if (!(tmp = ft_strdup(str)))
			return (FALSE);
	}
	else if ((tmp = ft_strjoin(*src, str)) == NULL)
	{
		free(*src);
		return (FALSE);
	}
	free(*src);
	*src = tmp;
	return (TRUE);
}

static char		ft_strjoinr_init(char **src, char *str, size_t n, char freestr)
{
	char		c;

	if (!str)
		return (FALSE);
	c = str[n];
	str[n] = '\0';
	if (ft_strjoinr(&(*src), str) == FALSE)
	{
		if (freestr == TRUE)
			free(str);
		else
			str[n] = c;
		return (FALSE);
	}
	if (freestr == TRUE)
		free(str);
	else
		str[n] = c;
	return (TRUE);
}

static char		*ft_nbcmd(char *str, size_t nbcmd, size_t *n)
{
	if (str)
	{
		if (ft_strncmp(str, "!#", 1) == 0)
		{
			*n = *n + 2;
			if (nbcmd == 0)
				return (ft_strdup("#"));
			else
				return (ft_itoa(nbcmd));
		}
	}
	return (NULL);
}

static void		ft_affprompt_norme(size_t nbcmd, char **env,
									char *str, char **tmp)
{
	char		*ret;
	size_t		n;
	size_t		save;

	n = 0;
	save = 0;
	while (str[n])
	{
		while (str[n] && (str[n] != '!' && str[n + 1] != '#') &&
				(str[n] != '!' && (str[n + 1] != 'W' || str[n + 1] != 'w')))
			n = n + 1;
		if ((str[n] == '!' && str[n + 1] == '#') ||
				(str[n] == '!' && (str[n + 1] == 'W' || str[n + 1] == 'w')))
		{
			ft_strjoinr_init(&(*tmp), str + save, n - save, FALSE);
			ret = (str[n] == '!' && str[n + 1] == '#') ?
				ft_nbcmd(str + n, nbcmd, &n) : ft_path(str + n, env, &n);
			ft_strjoinr_init(&(*tmp), ret, ft_strlen(ret), TRUE);
			save = n;
		}
		n = n + 1;
	}
	ft_strjoinr_init(&(*tmp), str + save, ft_strlen(str + save), FALSE);
}

void			ft_affprompt(size_t nbcmd, char **env)
{
	char	*str;
	char	*tmp;

	if (!(str = ft_strdup(PROMPT)))
		return ;
	tmp = NULL;
	ft_affprompt_norme(nbcmd, env, str, &tmp);
	ft_putendl_fd(tmp, 0);
	free(tmp);
	free(str);
}
