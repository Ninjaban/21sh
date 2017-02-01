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

static char	*ft_wordcpy(char *str, size_t start, size_t end)
{
	size_t	n;
	char	*cpy;

	n = 0;
	if ((cpy = ft_strnew(end - start + 1)) == NULL)
		return (NULL);
	while (start < end)
		cpy[n++] = str[start++];
	return (cpy);
}

char		*ft_getword(char *str, size_t pos)
{
	size_t	start;

	start = pos;
	if (!ft_isprint(str[pos - 1]))
		return (NULL);
	while (start > 0 && str[start] != ' ')
		start = start - 1;
	if (start == ' ')
		start = start + 1;
	return (ft_wordcpy(str, start, pos));
}

void		ft_opendir(t_lst **list, char *path)
{
	DIR				*dir;
	struct dirent	*files;

	if ((dir = opendir(path)) == NULL)
		return ;
	while ((files = readdir(dir)) != NULL)
		if (ft_strcmp(files->d_name, ".") && ft_strcmp(files->d_name, ".."))
			ft_list_push_back(&(*list), ft_strdup(files->d_name));
	closedir(dir);
}

t_lst		*ft_getexec(char **path)
{
	t_lst	*list;
	size_t	n;

	list = NULL;
	n = 0;
	if (!path)
		return (NULL);
	while (path[n])
		ft_opendir(&list, path[n++]);
	ft_free_tab(path);
	return (list);
}

char		*ft_color(char *color, char *str)
{
	char	*new;

	new = ft_strjoin(str, color);
	free(str);
	return (new);
}
