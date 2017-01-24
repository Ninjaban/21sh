/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:54:30 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/20 11:16:14 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static int	ft_builtins(t_cmd *cmds, t_sys **sys)
{
	if (ft_strcmp(cmds->name, "echo") == 0)
		ft_echo(cmds->argv, (*sys)->env);
	else if ((ft_strcmp(cmds->name, "setenv") == 0) ||
			 (ft_strcmp(cmds->name, "export") == 0))
		ft_setenv(cmds->argv[1], &((*sys)->env), FALSE);
	else if (ft_strcmp(cmds->name, "unsetenv") == 0)
		ft_unsetenv(&((*sys)->env), cmds->argv[1]);
	else if (ft_strcmp(cmds->name, "env") == 0)
		ft_env((*sys)->env);
	else if (ft_strcmp(cmds->name, "cd") == 0)
		ft_chdir(&((*sys)->env), cmds->argv[1]);
	else if (ft_strcmp(cmds->name, "alias") == 0)
		ft_alias(cmds, &((*sys)->alias));
	else if (ft_strcmp(cmds->name, "unalias") == 0)
		ft_unalias(cmds, &((*sys)->alias));
	else
		return (FALSE);
	return (TRUE);
}

static void	ft_exec_child(t_btree *root, t_sys **sys, int pdes[2])
{

}

static void	*ft_exec_node(t_btree *root, t_sys **sys)
{
	t_btree	*node;
	int		pdes[2];
	pid_t	child;

	node = root;
	pipe(pdes);
	if ((child = fork) == -1)
		return (ERROR_FORK);
	if (child == 0)
		ft_exec_child(root->left, &(*sys), pdes);
}

void		*ft_exec(t_sys **sys)
{
	t_btree	*node;
	pid_t	child;

	node = (*sys)->cmds;
	while (node)
	{
		if ((child = fork) == -1)
			return (ERROR_FORK);
		if (child == 0)
		{
			ft_exec_node(node->left, &(*sys));
			ft_error(ERROR_EXEC);
			exit(1);
		}
		wait(NULL);
		node = node->right;
	}
	return (NULL);
}
/*
void		*ft_exec(t_sys **sys)
{
	size_t	n;
	int		status;

	n = 0;
	while ((*sys)->cmds[n])
	{
		if ((*sys)->cmds[n]->name)
		{
			if (ft_strcmp((*sys)->cmds[n]->name, "exit") == 0)
				return (EXIT);
			if (ft_builtins((*sys)->cmds[n], &(*sys)) == FALSE)
			{
				if (((*sys)->cmds[n]->child = fork()) == -1)
					return (ERROR_FORK);
				if ((*sys)->cmds[n]->child == 0)
					ft_exec_child((*sys)->cmds[n], *sys);
				else
					wait(&status);
			}
		}
		n = n + 1;
	}
	return (NULL);
}
*/
