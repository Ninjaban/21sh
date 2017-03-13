/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_excl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:21:07 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/13 16:19:12 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static char	*ft_hist_last(t_lst *history)
{
	t_lst	*tmp;

	ft_log(TYPE_INFO, "!!");
	tmp = history;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp ? ((t_hist *)(tmp->data))->line : NULL);
}

void	ft_check_excl(t_sys **sys, char **str)
{
	char	*s;
	char	*cmd;

	ft_log(TYPE_INFO, "START");
	s = *str;
	while (*s)
	{
		cmd = NULL;
		if (*s == '!' && (*s + 1) != ' ' && (*s + 1) != '\t'
			&& (*s + 1) != '\n' && (*s + 1) != '=' && (*s + 1) != '(')
		{
			if (ft_strncmp(s, "!!", 1) == 0)
				cmd = ft_hist_last((*sys)->history);
			else if (ft_strncmp(s, "!?", 1) == 0)
				ft_log(TYPE_INFO, "??");
			else if (ft_strncmp(s, "!{", 1) == 0)
				ft_log(TYPE_INFO, "{}");
		}
		else if (*s == '^')
			;
		if (cmd)
			ft_log(TYPE_INFO, cmd);
		s++;
	}
	ft_log(TYPE_WARNING, "END");
}
