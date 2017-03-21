/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 09:09:52 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/13 10:11:29 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

t_alias			*ft_alias_new(char *key, char *value)
{
	t_alias	*new;

	if ((new = malloc(sizeof(t_alias))) == NULL)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = (value != NULL) ? ft_strdup(value) : NULL;
	new->next = NULL;
	return (new);
}

int				ft_alias_init(t_cmd *cmd, t_alias **alias)
{
	char	**tab;

	if ((tab = ft_strsplit(cmd->argv[1], "=")) == NULL)
	{
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (FALSE);
	}
	if (!tab[0])
	{
		free(tab);
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (FALSE);
	}
	if (((*alias) = ft_alias_new(tab[0], tab[1])) == NULL)
	{
		ft_free_tab(tab);
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (FALSE);
	}
	ft_free_tab(tab);
	return (TRUE);
}
