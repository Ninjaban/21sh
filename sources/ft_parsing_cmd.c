/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/06 12:34:35 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static char		**ft_tabcpy(char **tab)
{
	char		**dst;
	int			n;

	n = -1;
	if ((dst = malloc(sizeof(char *) * (ft_tablen(tab) + 1))) == NULL)
		return (NULL);
	while (tab[++n])
		dst[n] = ft_strdup(tab[n]);
	dst[n] = NULL;
	return (dst);
}

#include "error.h"

t_cmd			*ft_parsecmd(char *str)
{
	t_cmd		*cmd;
	char		**tab;
	char 		*tmp;

	ft_parse_parenthesis(&str, ' ', '\a');
	tmp = ft_strtrim(str);
	if (tmp)
		free(tmp);
	else
	{
		free(str);
		return (NULL);
	}
	if ((tab = ft_strsplit(str, " \t")) == NULL || !tab[0])
		return (NULL);
	if ((cmd = malloc(sizeof(t_cmd))) == NULL)
	{
		ft_free_tab(tab);
		return (NULL);
	}
	cmd->name = NULL;
	cmd->argv = NULL;
	ft_parenthesis_undo(&tab);
	if ((cmd->name = ft_strdup(tab[0])) == NULL)
	{
		ft_free_tab(tab);
		free(cmd);
		return (NULL);
	}
	cmd->argv = ft_tabcpy(tab);
	ft_free_tab(tab);
	free(str);
	return (cmd);
}
