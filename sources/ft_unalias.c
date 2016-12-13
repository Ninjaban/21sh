/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 09:20:20 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/08 15:35:17 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

static void	ft_alias_free(t_alias **alias)
{
	free((*alias)->value);
	free((*alias)->key);
	free((*alias));
	(*alias) = NULL;
}

void		ft_alias_remove(t_alias **alias)
{
	t_alias	*tmp;
	t_alias	*next;

	if (!alias)
		return ;
	tmp = *alias;
	while (tmp)
	{
		next = tmp->next;
		ft_alias_free(&(tmp));
		tmp = next;
	}
}

static void	ft_alias_remove_if(t_alias **alias, char *name)
{
	t_alias	*tmp;
	t_alias *prev;

	if (!alias)
		return ;
	tmp = *alias;
	prev = NULL;
	while (tmp)
		if (ft_strcmp(tmp->key, name) == 0)
		{
			if (prev == NULL)
				(*alias) = tmp->next;
			else
				prev->next = tmp->next;
			ft_alias_free(&(tmp));
			if (prev == NULL)
				tmp = *alias;
			else
				tmp = prev->next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
}

int			ft_unalias(t_cmd *cmd, t_alias **alias)
{
	size_t	n;

	if (cmd->argv[0] && cmd->argv[1])
	{
		n = 0;
		if (ft_strcmp(cmd->argv[1], "-a") == 0)
			ft_alias_remove(&(*alias));
		else
			while (cmd->argv[++n])
				ft_alias_remove_if(&(*alias), cmd->argv[n]);
	}
	return (TRUE);
}
