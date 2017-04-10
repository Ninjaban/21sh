/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:54:30 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 12:58:21 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

void		ft_exec_child(t_node *node, t_sys **sys)
{
	char	*name;

	if (ft_builtins(node->cmd) == FALSE)
	{
		if ((name = ft_access(node->cmd->name,
								(*sys)->env, (*sys)->shvar)) != NULL)
		{
			if (execve(name, node->cmd->argv, (*sys)->env) == -1)
			{
				wait(NULL);
				exit(ft_error_int(ERROR_EXEC, 1));
			}
			wait(NULL);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
		exit((ft_exec_builtins(node->cmd, sys) == TRUE) ? 0 : 1);
	}
	wait(NULL);
	exit(0);
}

int			ft_exec_open_file(char *str, char redir)
{
	char	*name;
	int		flags;
	int		fd;

	flags = 0;
	name = (str[0] != '/') ? ft_strjoin("./", str) : ft_strdup(str);
	if (access(name, F_OK) == 0)
		flags = (redir == REDIR_R) ? O_TRUNC : O_APPEND;
	if ((fd = open(name, O_WRONLY | O_CREAT | flags, 0644)) == -1)
	{
		free(name);
		return (ft_error_int(ERROR_NOTFOUND, -1));
	}
	free(name);
	return (fd);
}

void		ft_exec_file(t_node *node, char redir)
{
	char	*line;
	int		fd;

	if (node->cmd->name && node->cmd->name[0] != '&')
	{
		if ((fd = ft_exec_open_file(node->cmd->name, redir)) == -1)
			return ;
	}
	else if (node->cmd->name && ft_strcmp(node->cmd->name, "&-") == 0)
	{
		if ((fd = ft_exec_open_file("/dev/null", redir)) == -1)
			return ;
	}
	else
		fd = ft_atoi(node->cmd->name + 1);
	while (get_next_line(0, &line) == 1)
	{
		ft_putendl_fd(line, fd);
		ft_strdel(&line);
	}
	exit(1);
}

void		ft_exec_read_file(t_node *node)
{
	char	*name;
	char	*line;
	int		fd;

	name = ft_strjoin("./", node->cmd->name);
	if (access(name, F_OK) != 0)
	{
		ft_strdel(&name);
		return (ft_error(ERROR_NOTFOUND));
	}
	if ((fd = open(name, O_RDONLY)) == -1)
	{
		ft_strdel(&name);
		return (ft_error(ERROR_READ));
	}
	ft_strdel(&name);
	while (get_next_line(fd, &line) == 1)
		ft_putendl(line);
	exit(1);
}

void		ft_exec_read_boucle(t_node *node)
{
	char	*line;

	ft_putstr_fd("<key='", 0);
	ft_putstr_fd(node->cmd->name, 0);
	ft_putstr_fd("'>\n", 0);
	while (get_next_line(0, &line) == 1 &&
		ft_strcmp(node->cmd->name, line) != 0)
	{
		ft_putstr_fd("<key='", 0);
		ft_putstr_fd(node->cmd->name, 0);
		ft_putstr_fd("'>\n", 0);
		ft_putendl(line);
	}
	ft_putendl_fd("---", 0);
	exit(1);
}
