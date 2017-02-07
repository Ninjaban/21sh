/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:19:14 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/17 10:05:42 by jcarra           ###   ########.fr       */
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

void			ft_error(char *error);

#endif
