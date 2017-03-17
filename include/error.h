/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:14 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/16 12:45:33 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERROR_READ "Erreur de lecture."
# define ERROR_ALLOC "Erreur d'allocation memoire."
# define ERROR_FORK "Erreur lors de la création d'un nouveau processus."
# define ERROR_NOTFOUND "Fichier ou Executable introuvable."
# define ERROR_DNOTFOUND "Dossier introuvable."
# define ERROR_NOTDIR "Ceci n'est pas un dossier valide."
# define ERROR_PERMS "Vous n'avez pas les droits suffisants."
# define ERROR_EXEC "Erreur lors de l'execution."
# define ERROR_SYNTAX "Erreur de syntaxe."
# define ERROR_ENV "Erreur d'environement."
# define ERROR_RC "Erreur lors du traitement du ~/.42shrc."
# define ERROR_HISTORY "Erreur lors du traitement de l'historique."
# define ERROR_OPTION "Option invalide."
# define ERROR_LAUNCH "Le shell ne peut pas être lancé."
# define ERROR_SIGNAL "Erreur lors de la mise en place des signaux."
# define ERROR_TERM "Erreur lors de l'initialisation du terminal."
# define ERROR_KEYMAP "Erreur lors de l'initialisation du mappage de touche."
# define ERROR_VNOTFOUND "Variable non trouvée."
# define ERROR_HIST "Evénement introuvable."
# define ERROR_HIST_SYNTAX "Evénement incorrect."
# define ERROR_ALIAS "Cet alias existe déjà."

/*
**	ft_log pour faire des affichage d'information, de warning ou d'erreur
**	simple, a utiliser de preference.
**
**	les ft_error sont a utiliser en cas de return ou d'exit. Pour ft_error_int,
**	le second paramettre est la valeur de retour de la fonction.
*/

# define TYPE_INFO 0
# define TYPE_WARNING 1
# define TYPE_ERROR 2

void			ft_log(char type, char *log);

void			ft_error(char *error);
void			*ft_error_void(char *error);
int				ft_error_int(char *error, int exit);

#endif
