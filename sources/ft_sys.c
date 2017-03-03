/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sys.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 10:15:30 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/17 09:51:58 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

int			ft_sys_init(t_sys **sys)
{
	if ((*sys = malloc(sizeof(t_sys))) == NULL)
	{
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (1);
	}
	(*sys)->env = NULL;
	(*sys)->history = NULL;
	(*sys)->alias = NULL;
	(*sys)->cmds = NULL;
	return (0);
}

void		ft_free_alias(t_alias *alias)
{
	t_alias	*next;

	while (alias)
	{
		next = alias->next;
		free(alias->key);
		free(alias->value);
		free(alias);
		alias = next;
	}
}

void		ft_delete_node(void *node)
{
	t_node	*data;

	if (node)
	{
		if (((t_btree *)node)->item)
		{
			data = (t_node *)(((t_btree *)node)->item);
			if (data->cmd)
			{
				free(data->cmd->name);
				ft_free_tab(data->cmd->argv);
				free(((t_node *)(((t_btree *)node)->item))->cmd);
			}
			free(((t_btree *)node)->item);
		}
		free(node);
	}
}

void		ft_sys_free(t_sys *sys)
{
	if (sys->env)
		ft_free_tab(sys->env);
	if (sys->alias)
		ft_free_alias(sys->alias);
	if (sys->history)
		ft_list_clear(&(sys->history), &free);
	free(sys);
}
