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

/*
** FICHIER :: ALIAS
**   Fichier contenant le built-in alias
**
** LISTE DES FONCTIONS
**    > ft_alias_last
**    > ft_alias_check
**    > ft_alias_add
**    > ft_alias_aff
**   ft_alias
**
** INCLUDES
*/

#include "libft.h"
#include "error.h"
#include "shell.h"

/*
** STATIQUE :: ft_alias_last
**   Trouve le dernier alias enregistré
**
** PARAMETRES
**   t_alias*	first		chaîne d'alias à modifier
**
** VARIABLES
**   t_alias*	tmp			curseur pour parcourir les alias
**
** VALEUR DE RETOUR (t_alias*)
**   Retourne un pointeur vers le dernier alias de la liste
*/

static t_alias	*ft_alias_last(t_alias *first)
{
	t_alias		*tmp;

	tmp = first;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/*
** STATIQUE :: ft_alias_check
**   Check si un alias existe déjà
**
** PARAMETRES
**   t_alias*	str			chaîne d'alias à modifier
**   char*		key			la clef à rechercher
**
** VARIABLES
**   t_alias*	tmp			curseur pour parcourir les alias
**
** VALEUR DE RETOUR (int)
**   Retourne FALSE si la clé à été trouvée, TRUE autrement.
*/

static char		ft_alias_check(t_alias *alias, char *key)
{
	t_alias		*tmp;

	tmp = alias;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

/*
** STATIQUE :: ft_alias_add
**   Ajoute un alias à la liste
**
** PARAMETRES
**   t_cmd*		cmd			la commande parsée
**   t_alias*	str			chaîne d'alias à modifier
**
** VARIABLES
**   t_alias*	tmp			curseur pour parcourir les alias
**   char**		tab			commande splitée en tableau
**
** VALEUR DE RETOUR (int)
**   Retourne FALSE en cas d'erreur, TRUE autrement.
*/

static int		ft_alias_add(t_cmd *cmd, t_alias **alias)
{
	t_alias	*tmp;
	char	**tab;

	if ((tab = ft_strsplit(cmd->argv[1], "=")) == NULL)
		return (ft_error_int(ERROR_ALLOC, FALSE));
	if (!tab[0] || !tab[1])
	{
		ft_free_tab(tab);
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (FALSE);
	}
	if (ft_alias_check(*alias, tab[0]) == FALSE)
	{
		ft_free_tab(tab);
		return (ft_error_int(ERROR_ALIAS, FALSE));
	}
	tmp = (!(*alias)) ? *alias : ft_alias_last(*alias);
	if (!(*alias))
		tmp = ft_alias_new(tab[0], tab[1]);
	else
		tmp->next = ft_alias_new(tab[0], tab[1]);
	ft_free_tab(tab);
	if ((!(*alias) ? tmp : tmp->next) == NULL)
		return (ft_error_int(ERROR_ALLOC, FALSE));
	return (TRUE);
}

/*
** STATIQUE :: ft_alias_aff
**   Affiche les alias enregistrés
**
** PARAMETRES
**   t_alias*	str			chaîne d'alias à afficher
**
** VARIABLES
**   t_alias*	tmp			curseur pour parcourir les alias
*/


static void		ft_alias_aff(t_alias *alias)
{
	t_alias	*tmp;

	tmp = alias;
	while (tmp)
	{
		ft_putstr("alias ");
		ft_putstr(tmp->key);
		ft_putstr("=");
		ft_putendl(tmp->value);
		tmp = tmp->next;
	}
}

/*
** FONCTION :: ft_alias
**   Core du builtin alias : permet de créer et d'enregistrer des alias
**
** PARAMETRES
**   char*		cmd			la commande
**   t_alias**	alias		tableau des alias
**
** VALEUR DE RETOUR (int)
**   Retourne FALSE en cas d'erreur, TRUE autrement.
*/

int				ft_alias(t_cmd *cmd, t_alias **alias)
{
	if (!alias)
		return (FALSE);
	if (!cmd->argv[1])
		ft_alias_aff(*alias);
	else if (!(*alias))
	{
		if (ft_alias_init(cmd, &(*alias)) == FALSE)
			return (FALSE);
	}
	else if (ft_alias_add(cmd, &(*alias)) == FALSE)
		return (FALSE);
	return (TRUE);
}
