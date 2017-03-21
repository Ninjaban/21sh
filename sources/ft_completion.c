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

static void	ft_delete_tree(void *root)
{
	if (root)
	{
		if (((t_btree *)root)->item)
			free(((t_btree *)root)->item);
		free(root);
	}
}

int			ft_cmpf(void *tree, void *item)
{
	if (tree && item)
		return (ft_strcmp(((t_btree *)tree)->item, ((t_btree *)item)->item));
	return (0);
}

void		ft_completion(char **str, size_t pos, char **env, char dassault)
{
	t_btree			*list;
	char			*word;
	char			*tmp;

	if (!str || !(*str))
		return ;
	if ((word = ft_getword(*str, pos)) == NULL)
		return ;
	if ((tmp = ft_strtrim(word)) == NULL)
	{
		free(word);
		return ;
	}
	free(tmp);
	list = NULL;
	ft_completion_norme(word, &list, env);
	if ((tmp = ft_getprob(list, ft_getpattern(word))) != NULL)
		ft_setcompletion(&(*str), pos, tmp, dassault);
	free(word);
	if (list)
		btree_apply_suffix(list, &ft_delete_tree);
}

void		ft_removecompl(char **str)
{
	char	*new;
	char	*tmp;
	size_t	n;

	n = 0;
	if (!str || !(*str))
		return ;
	while ((*str)[n] && (*str)[n] != '\a')
		n = n + 1;
	if (!((*str)[n]))
		return ;
	(*str)[n++] = '\0';
	tmp = ft_strdup(*str);
	while ((*str)[n] && (*str)[n] != '\a')
		n = n + 1;
	new = ft_strjoin(tmp, (*str) + n + 1);
	free(tmp);
	free(*str);
	*str = new;
}

char		ft_checkcompl(char *str)
{
	size_t	n;

	n = 0;
	if (!str)
		return (0);
	while (str[n])
		if (str[n++] == '\a')
			return (1);
	return (0);
}
