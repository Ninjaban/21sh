/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 09:29:30 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/05 11:06:33 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FICHIER :: MAIN
**   Fichier contenant le main, qui initialise le programme.
**
** LISTE DES FONCTIONS
**    > ft_check_env
**    > ft_check_path
**    > ft_tabcpy
**   main
**
** INCLUDES
*/

#include "shell.h"
#include "error.h"
#include "terms.h"

/*
** STATIQUE :: ft_check_path
**   Check l'environnement à la recherche de la variable PWD
**
** PARAMETRES
**   char**		t			environnement à checker
**   char**		cpy			copie de l'environnement
**
** VARIABLES
**   char*		pwd			chemin du dossier courant
**   char*		var_pwd		PATH=chemin du dossier courant
**
** VALEUR DE RETOUR (int)
**   Si la variable PWD ne peut pas être initialisée (si elle n'est pas
**   présente dans l'environnement et qu'elle ne peut pas être récupérée,
**   retourne FALSE. Sinon, retourne TRUE.
*/

static int	ft_check_path(char **t, char ***cpy)
{
	char	*pwd;
	char	*var_pwd;

	if (ft_fpath(t, "PWD=") == ft_tablen(t))
	{
		if ((pwd = ft_strnew(4096)) == NULL)
		{
			ft_free_tab(*cpy);
			return (FALSE);
		}
		getcwd(pwd, 4096);
		if ((var_pwd = ft_strjoin("PWD=", pwd)) != NULL)
			ft_setenv(var_pwd, cpy, NULL, TRUE);
		free(pwd);
	}
	return (TRUE);
}

/*
** STATIQUE :: ft_tabcpy
**   Copie le tableau passé en paramètre.
**
** PARAMETRES
**   char**		t			le tableau à copier
**
** VARIABLES
**   char**		cpy			[RV] copie du tableau
**   int		n			compteur pour parcourir le tableau
**
** VALEUR DE RETOUR (char**)
**   En cas d'erreur, retourne NULL. Sinon, retourne le tableau copié.
*/

static char	**ft_tabcpy(char **t)
{
	char	**cpy;
	int		n;

	n = 0;
	if ((cpy = malloc(sizeof(char *) * (ft_tablen(t) + 1))) == NULL)
	{
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (NULL);
	}
	while (t[n])
		cpy[n++] = NULL;
	cpy[n] = NULL;
	n = -1;
	while (t[++n])
		if ((cpy[n] = ft_strdup(t[n])) == NULL)
		{
			ft_log(TYPE_ERROR, ERROR_ALLOC);
			ft_free_tab(cpy);
			return (NULL);
		}
	if (ft_check_path(t, &cpy) == FALSE)
		return (NULL);
	return (cpy);
}

/*
** FONCTION :: main
**   fonction main, qui initialise le shell avant de le lancer.
**
** VARIABLES
**   t_sys*		sys			variable système
*/

int			main(int ac, char **av, char **env)
{
	t_sys	*sys;

	(void)ac;
	(void)av;
	if (ft_sys_init(&sys) == 1)
		return (ft_error_int(ERROR_LAUNCH, 1));
	if (ft_termcaps_init(&sys->term_new, &sys->term_save) == FALSE)
	{
		ft_log(TYPE_WARNING, ERROR_TERM);
		return (ft_error_int(ERROR_LAUNCH, 1));
	}
	if ((sys->env = ft_tabcpy(env)) == NULL)
	{
		ft_log(TYPE_WARNING, ERROR_ENV);
		return (ft_error_int(ERROR_LAUNCH, 1));
	}
	if (ft_signal_stop() == FALSE)
		return (1);
	ft_shell(sys, FALSE, NULL, NULL);
	return (0);
}
