/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 09:01:22 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/06 21:49:37 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

/*
**	Copie le mot sur lequel l'entier pos pointe.
**	Mot est toute chaine separer par ' ' ou debut ou fin de chaine.
*/

static char	*ft_wordcpy(char *str, size_t start, size_t end)
{
	char	*cpy;

	if ((cpy = malloc(end - start + 1)) == NULL)
		return (NULL);
	while (start < end)
	{
		cpy[start] = str[start];
		start = start + 1;
	}
	cpy[start] = '\0';
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

/*
**	Copie tout les noms des fichier present de le path et les met dans une list.
*/

static void	ft_opendir(t_lst **list, char *path)
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

/*
**	Decoupe la chaine a partir du dernier '/'
**	getcdir renvois la partie precedant le '/'
**	getpattern revois la partie suivant le '/'
*/

static char	*ft_getcdir(char *str)
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

static char	*ft_getpattern(char *str)
{
	size_t	n;

	n = ft_strlen(str);
	while (n > 0 && str[n] != '/')
		n = n - 1;
	return (ft_strdup(str + n + 1));
}

/*
**	Main de la completion
*/

static char	*ft_getprob(t_lst *list, char *str)
{
	t_lst	*tmp;
	char	*pattern;

	pattern = ft_strjoin(str, "*");
	free(str);
	tmp = list;
	while (tmp && match(tmp->data, pattern) == 0)
		tmp = tmp->next;
	free(pattern);
	if (tmp)
		return (tmp->data + ft_strlen(pattern) - 1);
	return (NULL);
}

static char	*ft_color(char *color, char *str)
{
	char	*new;

	new = ft_strjoin(str, color);
	free(str);
	return (new);
}

static void	ft_setcompletion(char **str, size_t pos, char *try, char tabul)
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
	free(*str);
	*str = new;
}

void		ft_completion(char **str, size_t pos, char **env, char dassault)
{
	t_lst	*list;
	char	*word;
	char	*tmp;

	if (!str || !(*str))
		return ;
	if ((word = ft_getword(*str, pos)) == NULL)
		return ;
	if (word[0] == '/' || (word[0] == '.' && word[1] == '/'))
	{
		list = NULL;
		tmp = ft_getcdir(word);
		ft_opendir(&list, tmp);
		free(tmp);
	}
	else
		list = ft_getexec(ft_getpath(env));
	if ((tmp = ft_getprob(list, ft_getpattern(word))) != NULL)
		ft_setcompletion(&(*str), pos, tmp, dassault);
	ft_list_clear(&list, &free);
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
