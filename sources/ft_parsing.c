/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/05 11:01:18 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FILE :: PARSING
**   Fichier core du parsing, prépare et manage tout le processus.
**
** LISTE DES FONCTIONS
**    > ft_parsing_multicmd
**    > ft_add_node
**   ft_parsing_alias
**   ft_parsing
**
** INCLUDES
*/

#include "libft.h"
#include "shell.h"

/*
** STATIQUE :: ft_parsing_multicmd
**   Découpe la commande en fonction des redirections et des quotes et édite
**   l'arbre binaire en fonction. ?
**
** PARAMETRES
**   t_btree**	cmds		pointeur vers l'arbre binaire
**   char*		str			commande courante
**
** VARIABLES
**   size_t		n			compteur pour parcourir str, à l'envers
**   char		change		indicateur booléen pour les quotes
*/

static void		ft_parsing_multicmd(t_btree **cmds, char *str)
{
	size_t		n;
	char		change;

	n = ft_strlen(str);
	change = TRUE;
	while (n > 0)
	{
		if (str[n] == '\"' || str[n] == '\'')
			change = (change == TRUE) ? FALSE : TRUE;
		if (change == TRUE && (str[n] == '|' || str[n] == '<' || str[n] == '>'))
		{
			if (n > 0 && (str[n - 1] == '<' || str[n - 1] == '>'))
				n = n - 1;
			ft_init_node(&(*cmds), str + n, ft_get_redir_fd(str, n));
			n = n - 1;
			while (n > 0 && str[n] != ' ' && str[n] != '\t')
				n = n - 1;
			str[++n] = '\0';
		}
		n = n - 1;
	}
	ft_init_node(&(*cmds), str + n, ft_get_redir_fd(str, n));
}

/*
** FONCTION :: ft_add_node
**   Construit l'arbre binaire et crée les nodes de façon récursive.
**
** PARAMETRES
**   t_btree**	cmds		pointeur vers l'arbre binaire
**   char**		tab			tableau des commandes splitées ?
**   size_t		n			index de tab, incrémenté à chaque récursion ?
**
** VARIABLES
**   char		node		type de node (CMD, AND, OR)
*/

static void		ft_add_node(t_btree **cmds, char **tab, int n)
{
	char	node;

	node = FALSE;
	if (tab[n])
	{
		if (ft_strcmp(tab[n], ";") == 0 || ft_strcmp(tab[n], "&&") == 0
			|| ft_strcmp(tab[n], "||") == 0)
		{
			if (ft_strcmp(tab[n], ";") == 0)
				node = CMD;
			else if (ft_strcmp(tab[n], "&&") == 0)
				node = AND;
			else if (ft_strcmp(tab[n], "||") == 0)
				node = OR;
			btree_add_node(&(*cmds), btree_create_node(
					ft_new_node(node, NULL, FALSE, FALSE)), &ft_false_node);
			ft_add_node(&(*cmds), tab, n + 1);
		}
		else
		{
			ft_parsing_multicmd(&(*cmds), tab[n]);
			ft_add_node(&(*cmds), tab, n + 1);
		}
	}
}

/*
** FONCTION :: ft_parsing_alias
**   Check tous les mots de la commande, si c'est un alias, le remplace par
**   la valeur correspondante (sauf en cas d'inhibiteur)
**
** PARAMETRES
**   char**		str			commandes à parser ?
**   t_sys*		sys			variable système
**
** VARIABLES
**   size_t		n			compteur pour parcourir les commandes ?
**   char		change		indicateur booléen pour les inhibiteurs ?
*/

void			ft_parsing_alias(char **str, t_sys *sys)
{
	size_t		n;
	char		change;
	int			nb;

	n = 0;
	change = TRUE;
	while (*str && (*str)[n])
	{
		if ((*str)[n] == '\"' || (*str)[n] == '\'')
		{
			change = (change == TRUE) ? FALSE : TRUE;
			n = n + 1;
		}
		nb = 0;
		if (change == TRUE)
			nb = ft_check_alias(&(*str), sys->alias, n);
		if (nb != 0)
			n = n + nb;
		else
			while ((*str)[n] && (*str)[n] != ' ' && (*str)[n] != '\n' &&
					(*str)[n] != '\"' && (*str)[n] != '\'')
				n = n + 1;
		while ((*str)[n] && ((*str)[n] == ' ' || (*str)[n] == '\n'))
			n = n + 1;
	}
}

/*
** FONCTION :: ft_parsing_line
**   Initialise les variables et commence le parsing en fonction des aliases et
**   des points virgules.
**
** PARAMETRES
**   char*		str			ligne de commande à parser
**   t_sys*		sys			variable système
**
** VARIABLES
**   t_btree*	cmds		arbre binaire
**   char**		tab			table des commandes splitée ?
**   char*		tmp			buffer pour le parsing ?+
**
** VALEUR DE RETOUR (t_btree*)
**   Une fois le parsing terminé, retourne l'arbre. Si une erreur est
**   survenue, retourne NULL.
*/

t_btree			*ft_parsing_line(char *str, t_sys *sys)
{
	t_btree		*cmds;
	char		**tab;
	char		*tmp;

	tmp = ft_tild(ft_varenv(str, sys, TRUE), sys->env, sys->shvar);
	ft_parse_parenthesis_open_init(&tmp);
	tmp = ft_parsing_semicolon(tmp);
	ft_parsing_alias(&tmp, sys);
	ft_tild_file(&tmp, ';', '\a');
	if ((tab = ft_parsing_split(tmp)) == NULL)
	{
		free(str);
		free(tmp);
		return (NULL);
	}
	free(str);
	free(tmp);
	cmds = btree_create_node(ft_new_node(CMD, NULL, FALSE, FALSE));
	ft_add_node(&cmds, tab, 0);
	ft_free_tab(tab);
	return (cmds);
}

/*
** FONCTION :: ft_parsing
**   Initialise l'arbre binaire de tri et lance le processus de parsing
**
** PARAMETRES
**   char*		str			ligne de commande à parser
**   t_sys*		sys			variable système
**
** VARIABLES
**   t_btreee*	cmds		arbre binaire
**
** VALEUR DE RETOUR (t_btree*)
**   Une fois le parsing terminé, retourne l'arbre. Si une erreur est
**   survenue, retourne NULL.
*/

t_btree			*ft_parsing(char *str, t_sys *sys)
{
	t_btree		*cmds;

	if (!str)
		return (NULL);
	cmds = ft_parsing_line(str, sys);
	return (cmds);
}
