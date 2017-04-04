/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_error_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 10:57:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/04 10:57:00 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

char		ft_quotes(char c, char quotes)
{
	static char	save;

	if (c != '\"' && c != '\'')
		return (quotes);
	if (quotes == TRUE)
		return ((c == save) ? FALSE : TRUE);
	else
	{
		save = c;
		return (TRUE);
	}
}

char		*ft_gestion_error_check_redir(char *str)
{
	size_t	n;
	char	redir;
	char	quote;

	n = 0;
	redir = FALSE;
	quote = FALSE;
	while(str[n])
	{
		quote = ft_quotes(str[n], quote);
		if ((str[n] == '>' || ft_strncmp(str + n, ">>", 1) == 0) &&
				quote == FALSE)
		{
			if (redir == TRUE)
				return (ERROR_SYNTAX);
			else
				redir = TRUE;
		}
		else if ((str[n] == '<' || ft_strncmp(str + n, "<<", 1) == 0 ||
				str[n] == '|' || str[n] == ';' ||
				ft_strncmp(str + n, "&&", 1) == 0 ||
				ft_strncmp(str + n , "||", 1) == 0) && quote == FALSE)
			redir = FALSE;
		n = n + 1;
	}
	return (NULL);
}