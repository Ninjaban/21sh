/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 10:33:28 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 11:14:13 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int				ft_check_alias(char **str, t_alias *alias, int n)
{
	t_alias		*tmp;
	char		*new;
	char		*cpy;

	tmp = alias;
	while (tmp)
	{
		if ((ft_strncmp(*str + n, tmp->key, ft_strlen(tmp->key) - 1) == 0) &&
			(ft_strlen(tmp->key) <= ft_strlen(&((*str)[n]))) &&
			(((*str)[n + ft_strlen(tmp->key)] == ' ') ||
			((*str)[n + ft_strlen(tmp->key)] == '\0')))
		{
			(*str)[n] = '\0';
			cpy = ft_strdup((*str));
			new = ft_strjoin(cpy, tmp->value);
			free(cpy);
			cpy = ft_strjoin(new, &((*str)[n + ft_strlen(tmp->key)]));
			free(new);
			free(*str);
			*str = cpy;
			return ((int)ft_strlen(tmp->value));
		}
		tmp = tmp->next;
	}
	return (0);
}

void			ft_tild_file(char **str, char c, char r)
{
	size_t		n;
	char		change;

	n = 0;
	change = TRUE;
	if (!str || !(*str))
		return ;
	while ((*str)[n])
	{
		if ((*str)[n] == '\"' || (*str)[n] == '\'')
			change = (change == TRUE) ? FALSE : TRUE;
		if ((*str)[n] == c && (change == FALSE ||
			(n > 0 && ft_isalnum((*str)[n - 1]) == 1)))
			(*str)[n] = r;
		n = n + 1;
	}
}

static char		*ft_tild_new(char **tab, char **env, char **shvar)
{
	size_t		n;
	char		*genv;
	char		*new;
	char		*tmp;

	n = 0;
	new = ft_strdup(tab[0]);
	while (tab[++n])
	{
		genv = ft_getenv(env, shvar, "HOME=");
		tmp = ft_strjoin(new, genv);
		free(genv);
		free(new);
		new = ft_strjoin(tmp, tab[n]);
		free(tmp);
	}
	return (new);
}

char			*ft_tild(char *str, char **env, char **shvar)
{
	char		**tab;
	char		*tmp;
	char		*new;
	char		*home;

	ft_tild_file(&str, '~', '\a');
	if ((tab = ft_strsplit(str, "~")) == NULL)
		return (NULL);
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}
	new = ft_tild_new(tab, env, shvar);
	home = ft_getenv(env, shvar, "HOME=");
	tmp = (str[ft_strlen(str) - 1] == '~') ?
		ft_strjoin(new, home) : ft_strdup(new);
	free(home);
	free(new);
	new = tmp;
	ft_tild_file(&new, '\a', '~');
	ft_free_tab(tab);
	free(str);
	return (new);
}
