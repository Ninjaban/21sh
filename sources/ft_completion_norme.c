/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 09:01:22 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/23 14:53:17 by mrajaona         ###   ########.fr       */
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
	return (ft_strdup((str[n] == '/') ? str + n + 1 : str));
}

/*
**	Main de la completion
*/

char		*ft_getprob(t_btree *list, char *str)
{
	t_btree	*tmp;
	char	*ret;
	char	*pattern;
	char	exit;
	int		nb;

	exit = FALSE;
	tmp = list;
	while (exit == FALSE && (nb = ft_strcmp(tmp->item, str)) != 0)
		if (((nb < 0) ? tmp->left : tmp->right) == NULL)
			exit = TRUE;
		else
			tmp = (nb < 0) ? tmp->left : tmp->right;
	pattern = ft_strjoin(str, "*");
	if (tmp && (ft_strcmp(tmp->item, str) == 0 ||
			match(tmp->item, pattern) == 1))
		ret = tmp->item + ft_strlen(str);
	else
		ret = NULL;
	free(str);
	free(pattern);
	if (ret)
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
		new = ft_color("\a\x1b[4;38;5;249m", new);
	tmp = ft_strjoin(new, try);
	free(new);
	if (!tabul)
		tmp = ft_color("\033[0m\a", tmp);
	new = ft_strjoin(tmp, *str + pos);
	free(tmp);
	free(*str);
	*str = new;
}

void		ft_completion_norme(char *word, t_btree **list, char **env)
{
	char	*tmp;

	*list = ft_getexec(ft_getpath(env));
	tmp = ft_getcdir(word);
	if (word[0] == '/' || tmp[0] != '/')
		ft_opendir(&(*list), tmp);
	else
		ft_opendir(&(*list), "./");
	free(tmp);
}
