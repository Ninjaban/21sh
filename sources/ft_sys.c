/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sys.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 10:15:30 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/15 10:47:24 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

int			ft_sys_init(t_sys **sys)
{
	if ((*sys = malloc(sizeof(t_sys))) == NULL)
		return (ft_error_int(ERROR_ALLOC, 1));
	(*sys)->env = NULL;
	if (((*sys)->shvar = malloc(sizeof(char **))) == NULL)
	{
		free(*sys);
		return (ft_error_int(ERROR_ALLOC, 1));
	}
	if (((*sys)->ftvar = malloc(sizeof(char **))) == NULL)
	{
		free((*sys)->shvar);
		free(*sys);
		return (ft_error_int(ERROR_ALLOC, 1));
	}
	*((*sys)->shvar) = NULL;
	*((*sys)->ftvar) = NULL;
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

static void	ft_free_hist(void *data)
{
	if (data)
	{
		free(((t_hist *)data)->line);
		free(data);
	}
}

void		ft_sys_free(t_sys *sys)
{
	if (sys->env)
		ft_free_tab(sys->env);
	if (sys->shvar)
		ft_free_tab(sys->shvar);
	if (sys->ftvar)
		ft_free_tab(sys->ftvar);
	if (sys->keymap)
		free(sys->keymap);
	if (sys->alias)
		ft_free_alias(sys->alias);
	if (sys->history)
		ft_list_clear(&(sys->history), &ft_free_hist);
	free(sys);
}
