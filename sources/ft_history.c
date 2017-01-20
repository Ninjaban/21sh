/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 08:55:19 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/09 08:36:16 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

static int	ft_history_file(char **env, int flag)
{
	int		fd;
	char	*tmp;
	char	*path;

	if (!env)
		return (-1);
	if ((tmp = ft_getenv(env, "HOME=")) == NULL)
		return (-1);
	if ((path = ft_strjoin(tmp, "/.42sh_history")) == NULL)
	{
		free(tmp);
		return (-1);
	}
	fd = open(path, O_RDWR | O_CREAT | flag , 0644);
	free(tmp);
	free(path);
	return (fd);
}

static void	ft_history_suppr_first(t_lst **history)
{
	t_lst	*tmp;

	tmp = (*history)->next;
	ft_list_del(*history, &free);
	(*history) = tmp;
}

int			ft_history_maj(t_lst **history, char *line, char **env)
{
	t_lst	*tmp;
	char	*cpy;
	int		fd;

	if ((cpy = ft_strtrim(line)) == NULL)
		return (FALSE);
	free(cpy);
	if ((fd = ft_history_file(env, O_TRUNC)) == -1)
		return (FALSE);
	if (ft_list_size(*history) == HISTORY_SIZE)
		ft_history_suppr_first(&(*history));
	if (!(*history))
		*history = ft_create_elem((void *)line);
	else
		ft_list_push_back(&(*history), (void *)line);
	tmp = (*history);
	while (tmp)
	{
		ft_putendl_fd((char *)tmp->data, fd);
		tmp = tmp->next;
	}
	close(fd);
	return (TRUE);
}

int			ft_history_init(t_lst **history, char **env)
{
	size_t	n;
	char	*line;
	int		fd;

	if (HISTORY_SIZE <= 0 || !env)
		return (FALSE);
	n = 0;
	*history = NULL;
	if ((fd = ft_history_file(env, 0)) == -1)
		return (FALSE);
	line = NULL;
	while (n++ < HISTORY_SIZE && get_next_line(fd, &line) == 1)
	{
		if (!(*history))
			*history = ft_create_elem((void *)ft_strdup(line));
		else
			ft_list_push_back(&(*history), (void *)ft_strdup(line));
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
	return (TRUE);
}
