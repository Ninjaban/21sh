/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_error_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 10:57:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/04 11:28:23 by mrajaona         ###   ########.fr       */
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

size_t		ft_gestion_error_check_redir_norme(char *redir, char *str, size_t n)
{
	*redir = TRUE;
	while (str[n] == '>')
		n = n + 1;
	n = n - 1;
	return (n);
}

char		*ft_gestion_error_check_redir(char *str)
{
	size_t	n;
	char	redir;
	char	quote;

	n = 0;
	redir = FALSE;
	quote = FALSE;
	while (str[n])
	{
		quote = ft_quotes(str[n], quote);
		if ((str[n] == '>' || ft_strncmp(str + n, ">>", 1) == 0) &&
			quote == FALSE)
		{
			if (redir == TRUE)
				return (ERROR_SYNTAX);
			n = ft_gestion_error_check_redir_norme(&redir, str, n);
		}
		else if ((str[n] == '<' || ft_strncmp(str + n, "<<", 1) == 0 ||
				str[n] == '|' || str[n] == ';' ||
				ft_strncmp(str + n, "&&", 1) == 0 ||
				ft_strncmp(str + n, "||", 1) == 0) && quote == FALSE)
			redir = FALSE;
		n = n + 1;
	}
	return (NULL);
}

/*
** FUNCTION :: CHECK SEMICOLON SYNTAX
**   Check la syntaxe liée au point virgule ; (par ex [ls && ; pwd] ne doit pas
** 	 fonctionner).
**
** PARAMETRES
**   char*		cmd			la ligne de commande non trimée
**
** VARIABLES
**	 int		c			curseur pour explorer cmd
**
** VALEUR DE RETOUR
**   FALSE en cas d'erreur, TRUE sinon.
*/

char		*ft_check_semicolon_syntax(char *cmd)
{
	/*
	if (!ft_check_syntax_three(cmd) || !ft_check_syntax_start(cmd) ||
			!ft_check_syntax_before(cmd) || !ft_check_syntax_twins(cmd))
		return (ERROR_SYNTAX);
	*/
	if (!ft_check_syntax_three(cmd))
	{
		ft_putendl("THREE");
		return (ERROR_SYNTAX);
	}
	if (!ft_check_syntax_start(cmd))
	{
		ft_putendl("START");
		return (ERROR_SYNTAX);
	}
	if (!ft_check_syntax_before(cmd))
	{
		ft_putendl("BEFORE");
		return (ERROR_SYNTAX);
	}
	if (!ft_check_syntax_twins(cmd))
	{
		ft_putendl("TWINS");
		return (ERROR_SYNTAX);
	}
	return (NULL);
}