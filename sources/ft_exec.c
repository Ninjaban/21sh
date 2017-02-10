/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:54:30 by jcarra            #+#    #+#             */
/*   Updated: 2017/02/10 14:44:17 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static void	ft_exec_parent(pid_t child)
{
	int	status;

	if (child > 0)
	{
		if (waitpid(child, &status, 0) > 0)
		{
			if (WIFEXITED(status) && !WEXITSTATUS(status))
				ft_putstr(">> normal exit\n");
			else if (WIFEXITED(status) && WEXITSTATUS(status))
			{
				if (WEXITSTATUS(status) == 127)
					ft_putstr(">> exec fail\n");
				else
					ft_putstr(">> normal non-zero\n");
			}
			else
				ft_putstr(">> not normal exit\n");
		}
		else
			ft_putstr(">> waitpid fail\n");
	}
}

static char	*ft_exec_norme(t_btree *node, pid_t child, t_sys **sys)
{
	if (!node->left->item || !((t_node *)(node->left->item))->cmd)
		return (NULL);
	if (ft_strcmp_case(((t_node *)(node->left->item))->cmd->name,
					"exit") == 0)
	{
		if (((t_node *)(node->left->item))->cmd->argv[1])
			exit(ft_atoi(((t_node *)(node->left->item))->cmd->argv[1]));
		return (EXIT);
	}
	if (ft_builtins(((t_node *)(node->left->item))->cmd, &(*sys)) ==
		FALSE)
	{
		if ((child = fork()) == -1)
			return (ERROR_FORK);
		if (child == 0)
		{
			if (signal(SIGINT, SIG_DFL) == SIG_ERR)
				return (ERROR_FORK);
			ft_exec_child(node->left->item, &(*sys));
			exit(1);
		}
		ft_exec_parent(child);
	}
	else
		ft_putendl(">> exec builtin");
	wait(NULL);
	return (NULL);
}

void		*ft_exec(t_sys **sys, t_btree *node, char *tmp, pid_t child)
{
	while (node)
	{
		if (node->left && ((t_node *)(node->left->item))->redir == FALSE)
		{
			if ((tmp = ft_exec_norme(node, child, &(*sys))) != NULL)
				return (tmp);
		}
		else
		{
			if ((child = fork()) == -1)
				return (ERROR_FORK);
			if (child == 0)
			{
				if (signal(SIGINT, SIG_DFL) == SIG_ERR)
					return (ERROR_FORK);
				if ((tmp = ft_exec_node(node->left, &(*sys))) != NULL)
					return (tmp);
				ft_error(ERROR_EXEC);
				exit(1);
			}
			ft_exec_parent(child);
			wait(NULL);
		}
		node = node->right;
	}
	return (NULL);
}
