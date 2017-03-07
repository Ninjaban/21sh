/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:46:13 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/24 10:57:04 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static char	*ft_update_line(size_t *size, int *s, char *old, t_line *c)
{
	char	*new;

	if (*s == 0)
		return (old);
	new = (char *)ft_memalloc(sizeof(char) * (*size + *s + 1));
	if (old)
	{
		if (new)
		{
			new = (char *)ft_memcpy(new, old, sizeof(char) * *size);
			ft_memcpy(new + *size, c->str, sizeof(char) * *s);
			ft_memcpy((new + *size + *s), "\0", sizeof(char) * 1);
		}
		free(old);
	}
	*size += *s;
	if (!new)
		return (NULL);
	return (new);
}

static int	ft_size(t_line *c, size_t *size, char **line)
{
	int	s;

	if (c->size == 0)
		return (0);
	s = 0;
	while (s < c->size && c->str[s] != ENDL)
		s++;
	if ((*line = ft_update_line(size, &s, *line, c)) == NULL)
		return (-1);
	if (c->str[s] == ENDL)
	{
		s++;
		c->size = c->size - s;
		ft_memmove(c->str, c->str + s, c->size);
		ft_memset(c->str + c->size, 0, BUFF_SIZE - c->size);
		return (1);
	}
	return (0);
}

static int	ft_get_line(t_line *c, char **line)
{
	int		rd;
	int		ret;
	size_t	size;

	if (!(*line))
		return (-1);
	rd = 1;
	size = 0;
	while (rd > 0)
	{
		if ((ret = ft_size(c, &size, line)) != 0)
			return (ret);
		ft_memset(c->str, 0, BUFF_SIZE + 1);
		rd = read(c->fd, c->str, BUFF_SIZE);
		if (rd < 0)
			return (rd);
		c->size = rd;
		c->str[rd] = '\0';
	}
	if (size == 0)
		return (0);
	return (1);
}

static void	ft_init_fd(const int fd, t_line *list, int i)
{
	if (i >= NB_FD)
		return ;
	if (fd == -1 && i == -1)
		while (++i < NB_FD)
		{
			list[i].fd = fd;
			ft_memset(list[i].str, 0, sizeof(char) * (BUFF_SIZE + 1));
			list[i].size = 0;
		}
	else
	{
		list[i].fd = fd;
		ft_memset(list[i].str, 0, sizeof(char) * (BUFF_SIZE + 1));
		list[i].size = 0;
	}
}

int			get_next_line(const int fd, char **line)
{
	static t_line	list[NB_FD] = {{-1, {0}, 0}};
	int				i;
	int				ret;

	if (fd < 0 || line == NULL)
		return (-1);
	i = 0;
	if (list[0].fd == -1)
		ft_init_fd(-1, list, -1);
	while (i < NB_FD && list[i].fd != fd && list[i].fd != -1)
		i++;
	if (i == NB_FD)
		return (-1);
	if (list[i].fd == -1)
		ft_init_fd(fd, list, i);
	*line = (char *)ft_memalloc(1);
	ret = ft_get_line(&(list[i]), line);
	if (ret != 1 || list[i].size == 0)
	{
		while (++i < NB_FD)
			list[i - 1] = list[i];
		ft_init_fd(-1, list, NB_FD - 1);
	}
	return (ret);
}
