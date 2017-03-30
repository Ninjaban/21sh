/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:14 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/30 13:54:31 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FICHIER :: ERROR HEADER
**   Fichier contenant les messages d'erreur ainsi que les fonctions
**   destinées au traitement des erreurs (excepté ft_log qui permet également
**   d'afficher de simples avertissements).
*/

#ifndef ERROR_H
# define ERROR_H

/*
** DEFINES :: messages d'erreur
**   Tous les defines suivants sont des messages d'erreur.
*/

# define ERROR_READ			"Erreur de lecture."
# define ERROR_ALLOC		"Erreur d'allocation memoire."
# define ERROR_FORK			"Erreur lors de la création d'un nouveau processus."
# define ERROR_NOTFOUND		"Fichier ou Executable introuvable."
# define ERROR_DNOTFOUND	"Dossier introuvable."
# define ERROR_NOTDIR		"Ceci n'est pas un dossier valide."
# define ERROR_PERMS		"Vous n'avez pas les droits suffisants."
# define ERROR_EXEC			"Erreur lors de l'execution."
# define ERROR_SYNTAX		"Erreur de syntaxe."
# define ERROR_ENV			"Erreur d'environnement."
# define ERROR_RC			"Erreur lors du traitement du ~/.42shrc."
# define ERROR_HISTORY		"Erreur lors du traitement de l'historique."
# define ERROR_OPTION		"Option invalide."
# define ERROR_LAUNCH		"Le shell ne peut pas être lancé."
# define ERROR_SIGNAL		"Erreur lors de la mise en place des signaux."
# define ERROR_TERM			"Erreur lors de l'initialisation du terminal."
# define ERROR_KEYMAP	 "Erreur lors de l'initialisation du mappage de touche."
# define ERROR_VNOTFOUND	"Variable non trouvée."
# define ERROR_HIST			"Evénement introuvable."
# define ERROR_HIST_SYNTAX	"Evénement incorrect."
# define ERROR_ALIAS		"Cet alias existe déjà."
# define ERROR_BUILTIN		"Ce builtin n'existe pas."
# define ERROR_HELP			"Fichier d'aide introuvable."
# define ERROR_MACRO		"Cette macro n'existe pas."

/*
** DEFINES :: types
**   TYPE_INFO				l'erreur est une simple notification ?
**   TYPE_WARNING			l'erreur n'est pas critique ?
**   TYPE_ERROR				l'erreur est critique ?
*/

# define TYPE_INFO 			0
# define TYPE_WARNING 		1
# define TYPE_ERROR 		2

/*
** FONCTIONS
**   ft_log 				affichage d'informations, de warning ou d'erreurs
** 							simples, a utiliser de preference.
**   ft_error*				a utiliser en cas de return ou d'exit.
**	 ft_error_int			le second paramettre est la valeur de retour de la
** 																	   fonction.
*/

void			ft_log(char type, char *log);
void			ft_cmd_nfound(char *name);
void			ft_error(char *error);
void			*ft_error_void(char *error);
int				ft_error_int(char *error, int exit);

#endif
