/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 21:13:50 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/30 13:52:48 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FICHIER :: ECHO
**   Fichier contenant le built-in echo
**
** LISTE DES FONCTIONS
**    > ft_echo_token
**    > ft_echo_putstr
**   ft_echo
**
** INCLUDES
*/

#include "libft.h"
#include "ft_esc.h"
#include "shell.h"
#include "error.h"

/*
** STATIQUE :: ft_echo_token
**   Remplace les caractères avec backslash \ par leur équivalent normal
**
** PARAMETRES
**   char*      str         la commande
**   char*      token       le token
**   size_t     len         taille du token
**
** VARIABLES
**   size_t     i / n       curseurs pour parcourir token et str respectivement
*/

static void	ft_echo_token(char *str, char *token, size_t len)
{
	size_t	i;
	size_t	n;

	n = 0;
	i = 0;
	while (str[n] && i < len)
	{
		if (str[n] == '\n')
		{
			token[i] = 0x5c;
			i++;
			token[i] = 'n';
			n++;
		}
		else
			token[i] = str[n];
		n++;
		i++;
	}
	token[len] = '\0';
}

/*
** STATIQUE :: ft_echo_putstr
**   Affiche la chaine de caractère passée en paramètre et gère les caractères
**   d'échappement.
**
** PARAMETRES
**   char*		str			chaîne à afficher
**
** VARIABLES
**   char*		token		stocke les caractères de type \x
**   size_t		n			curseur pour parcourir la chaîne
**   size_t		len			longueur de la chaîne
**   size_t		count		caractères supplémentaires liés aux échappés
*/

static void	ft_echo_putstr(char *str)
{
	char	*token;
	size_t	n;
	size_t	len;
	size_t	count;

	if (!str)
		return ;
	len = ft_strlen(str);
	count = 0;
	n = -1;
	while (str[++n])
		if (IS_ESC(str[n]))
		{
			count++;
			n++;
		}
	if ((token = ft_strnew(len + count)) == NULL)
		return (ft_putstr(str));
	ft_echo_token(str, token, len + count);
	ft_putstr(token);
	free(token);
}

/*
** FONCTION :: ft_echo
**   Core du builtin echo : affiche le contenu des paramètres, dans l'ordre,
**   séparés par un espace.
**
** PARAMETRES
**   char**		argv		arguments
**
** VARIABLES
**   size_t		n			curseur pour parcourir les arguments
**
** VALEUR DE RETOUR (int)
**   Retourne toujours TRUE.
*/

int			ft_echo(char **argv)
{
	size_t	n;

	n = 1;
	while (argv[n])
	{
		ft_echo_putstr(argv[n]);
		if (argv[++n])
			ft_putstr(" ");
	}
	ft_putstr("\n");
	return (TRUE);
}
