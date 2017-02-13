/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:54:30 by jcarra            #+#    #+#             */
/*   Updated: 2017/02/13 11:56:34 by mrajaona         ###   ########.fr       */
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
			{ft_putstr(">> normal exit\n"); return (0);}
			else if (WIFEXITED(status) && WEXITSTATUS(status))
			{
				if (WEXITSTATUS(status) == 127)
				{ft_putstr(">> exec fail\n"); return (1);}
				else
				{ft_putstr(">> normal non-zero\n"); return (1);}
			}
			else
			{ft_putstr(">> not normal exit\n"); return (1);}
		}
		else
		{ft_putstr(">> waitpid fail\n"); return (1);}
	}
	return (0);
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
	int	ret;

	ret = 0;
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
			ret = ft_exec_parent(child);
			wait(NULL);
		}
		if (ret == 0 && ((t_node *)(node->item))->node == OR)
			while (node && ((t_node *)(node->item))->node == OR)
				node = node->right;
		else if (ret != 0 && ((t_node *)(node->item))->node == AND)
			while (node && ((t_node *)(node->item))->node == AND)
				node = node->right;
		else
			node = node->right;
	}
	return (NULL);
}
