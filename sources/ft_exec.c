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
		ft_echo(cmds->argv);
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

static void	ft_exec_child(t_node *node, t_sys **sys)
{
	char	*name;

	if ((ft_builtins(node->cmd, &(*sys)) == FALSE) && (name = ft_access(node->cmd->name, (*sys)->env)) != NULL)
		if (execve(name, node->cmd->argv, (*sys)->env) == -1)
			ft_error(ERROR_EXEC);
	exit(1);
}

static void ft_init_redir(t_node *node, int pdes[2], char way)
{
    if (node->redir == PIPE || node->redir == REDIR_R || node->redir == CONCAT_R)
    {
        dup2(pdes[(way == LEFT) ? PIPE_IN : PIPE_OUT], (way == LEFT) ? STDOUT_FILENO : STDIN_FILENO);
        close(pdes[(way == LEFT) ? PIPE_OUT : PIPE_IN]);
    }
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
	{
        ft_init_redir(node, pdes, LEFT);
        ft_exec_node(root->left, &(*sys));
        exit(1);
	}
    ft_init_redir(node, pdes, RIGHT);
	ft_exec_child(root->right->item, &(*sys));
	return (NULL);
}

/*
static void	*ft_exec_node(t_btree *root, t_sys **sys)
{
	t_btree	*node;
	int		pdes[2];
	pid_t	child;

	node = root;
	pipe(pdes);
    if (((t_node *)(node->left->item))->redir != FALSE)
    {
        if ((child = fork) == -1)
            return (ERROR_FORK);
        if (child == 0)
            ft_exec_node(root->left, &(*sys), pdes);
    }
}
*/

void		*ft_exec_node(t_btree *root, t_sys **sys)
{
	char	*tmp;

	if (((t_node *)(root->item))->redir == FALSE)
		ft_exec_child(root->item, &(*sys));
	else if ((tmp = ft_exec_rdr(root, &(*sys))) != NULL)
		return (tmp);
	return (NULL);
}

void		*ft_exec(t_sys **sys)
{
	t_btree	*node;
	pid_t	child;
	char	*tmp;

	node = (*sys)->cmds;
	while (node)
	{
		if ((child = fork()) == -1)
			return (ERROR_FORK);
		if (child == 0)
		{
			if ((tmp = ft_exec_node(node->left, &(*sys))) != NULL)
				return (tmp);
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
