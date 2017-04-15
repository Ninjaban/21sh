/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:54:30 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/17 10:42:41 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static void	ft_init_redir_all(int pdes[2], char way)
{
	if (dup2(pdes[(way == LEFT) ? PIPE_IN : PIPE_OUT], STDIN_FILENO) == -1)
		ft_log(TYPE_WARNING, "DUP FAIL");
	if (dup2(pdes[(way == LEFT) ? PIPE_IN : PIPE_OUT], STDOUT_FILENO) == -1)
		ft_log(TYPE_WARNING, "DUP FAIL");
	if (dup2(pdes[(way == LEFT) ? PIPE_IN : PIPE_OUT], STDERR_FILENO) == -1)
		ft_log(TYPE_WARNING, "DUP FAIL");
}

static void	ft_init_redir(t_node *node, int pdes[2], char way)
{
	int		stdout;

	if (node->redir == PIPE || node->redir == REDIR_R ||
		node->redir == CONCAT_R || node->redir == REDIR_L ||
		node->redir == CONCAT_L)
	{
		if (node->fd == 1)
			stdout = STDOUT_FILENO;
		else if (node->fd == 2)
			stdout = STDERR_FILENO;
		else if (node->fd == -1)
			ft_init_redir_all(pdes, way);
		else
			stdout = node->fd;
		if (dup2(pdes[(way == LEFT) ? PIPE_IN : PIPE_OUT],
				 (way == LEFT) ? stdout : STDIN_FILENO) == -1)
			ft_log(TYPE_WARNING, "DUP FAIL");
		close(pdes[(way == LEFT) ? PIPE_OUT : PIPE_IN]);
	}
}

static void	ft_exec_rdr_norme(t_btree *root, t_node *node, int pdes[2],
								t_sys **sys)
{
	ft_init_redir(node, pdes, LEFT);
	if (node->redir == REDIR_L)
		ft_exec_read_file(root->right->item);
	else if (node->redir == CONCAT_L)
		ft_exec_read_boucle(root->right->item);
	else
		ft_exec_node(root->left, &(*sys));
	exit(1);
}

static void	*ft_exec_rdr(t_btree *root, t_sys **sys)
{
	t_node	*node;
	pid_t	child;
	int		pdes[2];

	pipe(pdes);
	node = (t_node *)(root->item);
	if ((child = fork()) == -1)
		return (ERROR_FORK);
	if (child == 0)
		ft_exec_rdr_norme(root, node, pdes, &(*sys));
	ft_init_redir(node, pdes, RIGHT);
	if (node->redir == REDIR_R || node->redir == CONCAT_R)
		ft_exec_file(root->right->item, (node->redir == REDIR_R) ?
										REDIR_R : CONCAT_R);
	else if (node->redir == REDIR_L)
		ft_exec_node(root->left, &(*sys));
	else if (node->redir == CONCAT_L)
	{
		wait(NULL);
		ft_exec_node(root->left, &(*sys));
	}
	else
		ft_exec_child(root->right->item, &(*sys));
	return (NULL);
}

void		*ft_exec_node(t_btree *root, t_sys **sys)
{
	char	*tmp;

	if (((t_node *)(root->item))->redir == FALSE)
		ft_exec_child(root->item, &(*sys));
	else if ((tmp = ft_exec_rdr(root, &(*sys))) != NULL)
		return (tmp);
	return (NULL);
}
