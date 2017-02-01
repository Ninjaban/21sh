/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 09:01:22 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/30 09:11:59 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "shell.h"

char		*ft_getcdir(char *str)
{
	char	*tmp;
	char	c;
	size_t	n;

	n = ft_strlen(str);
	while (n > 0 && str[n] != '/')
		n = n - 1;
	if (n == 0)
		tmp = ft_strdup("/");
	else
	{
		c = str[n];
		str[n] = '\0';
		tmp = ft_strdup(str);
		str[n] = c;
	}
	return (tmp);
}

char		*ft_getpattern(char *str)
{
	size_t	n;

	n = ft_strlen(str);
	while (n > 0 && str[n] != '/')
		n = n - 1;
	return (ft_strdup((n == 0) ? str : str + n + 1));
}

/*
**	Main de la completion
*/

char		*ft_getprob(t_lst *list, char *str)
{
	t_lst	*tmp;
	char	*pattern;
	char	*ret;

	pattern = ft_strjoin(str, "*");
	tmp = list;
	while (tmp && ft_strcmp(tmp->data, str) != 0 &&
			match(tmp->data, pattern) == 0)
		tmp = tmp->next;
	free(str);
	if (tmp)
		ret = tmp->data + ft_strlen(pattern) - 1;
	free(pattern);
	if (tmp)
		return (ret);
	return (NULL);
}

void		ft_setcompletion(char **str, size_t pos, char *try, char tabul)
{
	char	*new;
	char	*tmp;
	char	c;

	c = (*str)[pos];
	(*str)[pos] = '\0';
	new = ft_strdup(*str);
	(*str)[pos] = c;
	if (!tabul)
		new = ft_color("\a\e[1;4m", new);
	tmp = ft_strjoin(new, try);
	free(new);
	if (!tabul)
		tmp = ft_color("\e[0m\a", tmp);
	new = ft_strjoin(tmp, *str + pos);
	free(tmp);
	free(*str);
	*str = new;
}

void		ft_completion_norme(char *word, t_lst **pattern, t_lst **list,
								char **env)
{
	char	*tmp;

	if (word[0] == '/' || (word[0] == '.' && word[1] == '/'))
	{
		tmp = ft_getcdir(word);
		ft_opendir(&(*pattern), tmp);
		free(tmp);
	}
	else if (!(*list))
	{
		*list = ft_getexec(ft_getpath(env));
		ft_list_sort(&(*list), &ft_strcmp);
	}
}
