/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:54:30 by jcarra            #+#    #+#             */
/*   Updated: 2017/02/28 13:57:36 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static int	ft_exec_parent(pid_t child)
{
	int	status;

	if (child > 0)
	{
		if (waitpid(child, &status, 0) > 0)
		{
			if (WIFEXITED(status) && !WEXITSTATUS(status))
			{
				ft_log(TYPE_INFO, ">> normal exit"); // A enlever
				return (0);
			}
			else
			{
				ft_log(TYPE_INFO, ">> not normal exit"); // A enlever
				return (1);
			}
		}
	}
	return (0);
}

static char	*ft_exec_norme(t_btree *node, pid_t child, t_sys **sys, int *ret)
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
	if (ft_builtins(((t_node *)(node->left->item))->cmd) ==
		FALSE)
	{
		if ((child = fork()) == -1)
			return (ERROR_FORK);
		if (child == 0)
		{
			if (ft_signal_start() == FALSE)
				return (ERROR_FORK);
			ft_exec_child(node->left->item, &(*sys));
			exit(1);
		}
		*ret = ft_exec_parent(child);
	}
	else if (ft_exec_builtins(((t_node *)(node->left->item))->cmd,
								&(*sys)) == TRUE)
	{
		ft_log(TYPE_INFO, ">> exec builtin"); 	// A enlever
		*ret = 0;
	}
	else
	{
		ft_log(TYPE_INFO, ">> fail builtin"); 	// A enlever
		*ret = 1;
	}
	wait(NULL);
	return (NULL);
}

void		*ft_exec(t_sys **sys, t_btree *node, char *tmp, pid_t child)
{
	int	ret;

	ret = 0;
	while (node)
	{
		if (ret == 0 && ((t_node *)(node->item))->node == OR)
			while (node && ((t_node *)(node->item))->node == OR)
				node = node->right;
		else if (ret != 0 && ((t_node *)(node->item))->node == AND)
			while (node && ((t_node *)(node->item))->node == AND)
				node = node->right;
		if (!node)
			return (NULL);
		if (node->left && ((t_node *)(node->left->item))->redir == FALSE)
		{
			if ((tmp = ft_exec_norme(node, child, &(*sys), &ret)) != NULL)
				return (tmp);
		}
		else
		{
			if ((child = fork()) == -1)
				return (ERROR_FORK);
			if (child == 0)
			{
				ft_log(TYPE_INFO, ">> exec fork");
				if (ft_signal_start() == FALSE)
					return (ERROR_FORK);
				if ((tmp = ft_exec_node(node->left, &(*sys))) != NULL)
					return (tmp);
				ft_log(TYPE_ERROR, ERROR_EXEC);
				exit(1);
			}
			ret = ft_exec_parent(child);
			wait(NULL);
		}
		node = node->right;
	}
	return (NULL);
}
