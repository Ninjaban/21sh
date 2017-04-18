/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:41:52 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/06 17:05:15 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		ft_check_syntax_three(char *cmd)
{
	int		i;
	int		w;
	char	b;

	i = -1;
	while (cmd[++i])
	{
		if (IS_INHIB(cmd[i]) && (b = cmd[i]))
		{
			i++;
			while (cmd[i] && cmd[i] != b)
				i++;
			i--;
		}
		w = 0;
		while (cmd[i] && IS_REDIR_CHAR(cmd[i]) && (w = w + 1))
			i++;
		if (w > 3)
			return (FALSE);
		if (w == 3 && !IS_CCA(cmd, i))
			return (FALSE);
		if (!cmd[i])
			break ;
	}
	return (TRUE);
}

char		ft_check_syntax_start(char *cmd)
{
	int		i;
	int		c;
	char	b;

	c = 0;
	i = -1;
	while (cmd[++i])
	{
		if (IS_INHIB(cmd[i]))
		{
			b = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != b)
				i++;
			i--;
		}
		if (IS_BLANK(cmd[i]))
			continue ;
		c = (!IS_REDIR_CHAR(cmd[i]) ? 1 : c);
		c = (cmd[i] == ';' ? 0 : c);
		if (IS_REDIR_CHAR(cmd[i]) && c == 0)
			return (FALSE);
	}
	return (TRUE);
}

char		ft_check_syntax_before(char *cmd)
{
	int		i;
	int		c;
	char	b;

	i = ft_strlen(cmd);
	c = 0;
	while (--i >= 0)
	{
		if (IS_INHIB(cmd[i]))
		{
			b = cmd[i];
			i--;
			while (i >= 0 && cmd[i] != b)
				i--;
		}
		if (IS_BLANK(cmd[i]))
			continue ;
		if (!IS_REDIR_CHAR(cmd[i]))
			c = 1;
		if (cmd[i] == ';')
			c = 0;
		if (IS_REDIR_CHAR(cmd[i]) && c == 0)
			return (FALSE);
	}
	return (TRUE);
}

char		ft_check_syntax_twins(char *cmd)
{
	int		i;
	char	b;

	i = -1;
	while (cmd[++i])
	{
		if (IS_INHIB(cmd[i]) && (b = cmd[i]))
		{
			i++;
			while (cmd[i] && cmd[i] != b)
				i++;
			i--;
		}
		if (IS_REDIR_CHAR(cmd[i]) && (b = cmd[i]))
		{
			i++;
			while (IS_BLANK(cmd[i]))
				i++;
			if ((IS_REDIR_CHAR(cmd[i])) && (cmd[i] != b) && (!IS_AC(cmd, i)))
				return (FALSE);
		}
	}
	return (TRUE);
}
