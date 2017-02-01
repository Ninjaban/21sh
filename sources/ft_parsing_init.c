/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/11 08:42:36 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_node			*ft_new_node(char node, char *str, char redir, int fd)
{
	t_node		*new;

	if ((new = malloc(sizeof(t_node))) == NULL)
		return (NULL);
	new->node = node;
	new->cmd = (str) ? ft_parsecmd(ft_strdup(str)) : NULL;
	new->redir = redir;
	new->fd = fd;
	return (new);
}

static char		ft_get_redir(char *str, size_t i)
{
	char		redir;

	redir = (str[i] == '|') ? PIPE : FALSE;
	redir = (redir == FALSE && str[i] == '>' && str[i + 1] != '>') ?
		REDIR_R : redir;
	redir = (redir == FALSE && str[i] == '>' && str[i + 1] == '>') ?
		CONCAT_R : redir;
	redir = (redir == FALSE && str[i] == '<' && str[i + 1] != '<') ?
		REDIR_L : redir;
	redir = (redir == FALSE && str[i] == '<' && str[i + 1] == '<') ?
		CONCAT_L : redir;
	return (redir);
}

int				ft_get_redir_fd(char *str, size_t i)
{
	size_t		n;

	n = 1;
	if (i == 0 || str[i] != '>')
		return (1);
	if (ft_isdigit(str[i - 1]) == FALSE)
		return (1);
	while (i - n > 0 && ft_isdigit(str[i - n]))
		n = n + 1;
	return (ft_atoi(str + ((i - n == 0) ? i - n : i - n + 1)));
}

void			ft_init_node(t_btree **cmds, char *str, int fd)
{
	size_t		n;
	char		redir;

	n = 0;
	if ((redir = ft_get_redir(str, n)) != FALSE)
	{
		btree_add_node(&(*cmds), btree_create_node(
						ft_new_node(TRUE, NULL, redir, fd)), &ft_true_node);
		while (str[n] == '|' || str[n] == '<' || str[n] == '>')
			n = n + 1;
	}
	btree_add_node(&(*cmds), btree_create_node(
					ft_new_node(TRUE, str + n, FALSE, FALSE)), &ft_true_node);
}
