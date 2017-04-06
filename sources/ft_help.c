/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:39:19 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 10:47:26 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FICHIER :: HELP
**   Fichier contenant le built-in help
**
** LISTE DES FONCTIONS
**    > ft_help_check
**    > ft_help_strjoin
**    > ft_help_getname
**    > ft_help_init_argv
**   ft_help
**
** INCLUDES
*/

#include "shell.h"
#include "error.h"

static char	ft_help_check(char *name)
{
	char	check;

	check = FALSE;
	check = (ft_strcmp(name, "echo") == 0) ? TRUE : check;
	check = (ft_strcmp(name, "setenv") == 0) ? TRUE : check;
	check = (ft_strcmp(name, "export") == 0) ? TRUE : check;
	check = (ft_strcmp(name, "set") == 0) ? TRUE : check;
	check = (ft_strcmp(name, "unset") == 0) ? TRUE : check;
	check = (ft_strcmp(name, "unsetenv") == 0) ? TRUE : check;
	check = (ft_strcmp(name, "env") == 0) ? TRUE : check;
	check = (ft_strcmp(name, "cd") == 0) ? TRUE : check;
	check = (ft_strcmp(name, "alias") == 0) ? TRUE : check;
	check = (ft_strcmp(name, "unalias") == 0) ? TRUE : check;
	check = (ft_strcmp(name, "keymap") == 0) ? TRUE : check;
	check = (ft_strcmp(name, "history") == 0) ? TRUE : check;
	check = (ft_strcmp(name, "help") == 0) ? TRUE : check;
	return (check);
}

static char	*ft_help_strjoin(char *src, char *join)
{
	char	*new;

	new = ft_strjoin(src, join);
	free(src);
	return (new);
}

/*
** FONCTION :: ft_help_getname
**   Prépare
**
** PARAMETRES
**   char*		path		path du .help
**
** VARIABLES
**   char**		argv		arguments
**
** VALEUR DE RETOUR (char**)
**   Retourne NULL en cas d'erreur, ARGV autrement.
*/

static char	*ft_help_getname(char **av, char **env, char **shvar)
{
	char	*home;
	char	*path;

	if ((home = ft_getenv(env, shvar, "HOME=")) == NULL)
		return (ft_error_void(ERROR_HELP));
	if ((path = ft_help_strjoin(home, "/.help/")) == NULL)
		return (ft_error_void(ERROR_ALLOC));
	if ((path = ft_help_strjoin(path, (av[1]) ? av[1] : "help")) == NULL)
		return (ft_error_void(ERROR_ALLOC));
	if ((path = ft_help_strjoin(path, ".help")) == NULL)
		return (ft_error_void(ERROR_ALLOC));
	return (path);
}

/*
** FONCTION :: ft_help_init_argv
**   Prépare les arguments de help en cat /file
**
** PARAMETRES
**   char*		path		path du .help
**
** VARIABLES
**   char**		argv		arguments
**
** VALEUR DE RETOUR (char**)
**   Retourne NULL en cas d'erreur, ARGV autrement.
*/

static char	**ft_help_init_argv(char *path)
{
	char	**argv;

	if (!path)
		return (NULL);
	if ((argv = malloc(sizeof(char *) * 3)) == NULL)
	{
		free(path);
		return (NULL);
	}
	if ((argv[0] = ft_strdup("/bin/cat")) == NULL)
	{
		free(path);
		free(argv);
		return (NULL);
	}
	argv[1] = path;
	argv[2] = NULL;
	return (argv);
}

/*
** FONCTION :: ft_help
**   Core du builtin help : affiche la liste des built ins
**
** PARAMETRES
**   char**		av			arguments
**   char**		env			environnement
**   char**		shvar		variables locales
**
** VARIABLES
**   char**		argv		arguments... ?
** 	 pid_t		child		pid pour le fork
**
** VALEUR DE RETOUR (char)
**   Retourne FALSE en cas d'erreur, TRUE autrement.
*/

char		ft_help(char **av, char **env, char **shvar)
{
	char	**argv;
	pid_t	child;

	if (av[1] && ft_help_check(av[1]) == FALSE)
		return (ft_error_int(ERROR_BUILTIN, FALSE));
	if ((argv = ft_help_init_argv(ft_help_getname(av, env, shvar))) == NULL)
		return (FALSE);
	if ((child = fork()) == -1)
	{
		ft_free_tab(argv);
		return (ft_error_int(ERROR_FORK, FALSE));
	}
	else if (child == 0)
	{
		execve("/bin/cat", argv, env);
		exit(ft_error_int(ERROR_EXEC, 1));
	}
	wait(NULL);
	ft_free_tab(argv);
	return (TRUE);
}
