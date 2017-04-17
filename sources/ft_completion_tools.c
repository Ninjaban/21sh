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
	if (str[start] == ' ')
		start = start + 1;
	return (ft_wordcpy(str, start, pos));
}

void		ft_opendir(t_btree **list, char *path, char diropen)
{
	DIR				*dir;
	struct dirent	*files;

	if ((dir = opendir(path)) == NULL)
		return ;
	while ((files = readdir(dir)) != NULL)
		if (ft_strcmp(files->d_name, ".") && ft_strcmp(files->d_name, ".."))
		{
			if (diropen == TRUE)
				btree_add_node(&(*list),
					btree_create_node((files->d_type == DT_DIR) ?
					ft_strjoin(files->d_name, "/") : ft_strdup(files->d_name)),
					&ft_cmpf);
			else if (files->d_type != DT_DIR)
				btree_add_node(&(*list),
					btree_create_node(ft_strdup(files->d_name)), &ft_cmpf);
		}
	closedir(dir);
}

t_btree		*ft_getexec(char **path)
{
	t_btree	*list;
	size_t	n;

	n = 0;
	if (!path)
		return (NULL);
	list = btree_create_node(ft_strdup("null"));
	while (path[n])
		ft_opendir(&list, path[n++], FALSE);
	btree_add_node(&(list), btree_create_node(ft_strdup("alias")), &ft_cmpf);
	btree_add_node(&(list), btree_create_node(ft_strdup("exit")), &ft_cmpf);
	btree_add_node(&(list), btree_create_node(ft_strdup("unalias")), &ft_cmpf);
	btree_add_node(&(list), btree_create_node(ft_strdup("setenv")), &ft_cmpf);
	btree_add_node(&(list), btree_create_node(ft_strdup("unsetenv")), &ft_cmpf);
	btree_add_node(&(list), btree_create_node(ft_strdup("export")), &ft_cmpf);
	btree_add_node(&(list), btree_create_node(ft_strdup("cd")), &ft_cmpf);
	btree_add_node(&(list), btree_create_node(ft_strdup("keymap")), &ft_cmpf);
	btree_add_node(&(list), btree_create_node(ft_strdup("history")), &ft_cmpf);
	btree_add_node(&(list), btree_create_node(ft_strdup("help")), &ft_cmpf);
	btree_add_node(&(list), btree_create_node(ft_strdup("set")), &ft_cmpf);
	btree_add_node(&(list), btree_create_node(ft_strdup("unset")), &ft_cmpf);
	btree_add_node(&(list), btree_create_node(ft_strdup("env")), &ft_cmpf);
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
