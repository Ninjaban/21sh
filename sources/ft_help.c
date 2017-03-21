/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:39:19 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/15 15:28:54 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*ft_help_getname(char **av, char **env)
{
	char	*home;
	char	*path;

	if ((home = ft_getenv(env, "HOME=")) == NULL)
		return (ft_error_void(ERROR_HELP));
	if ((path = ft_help_strjoin(home, "/.help/")) == NULL)
		return (ft_error_void(ERROR_ALLOC));
	if ((path = ft_help_strjoin(path, (av[1]) ? av[1] : "help")) == NULL)
		return (ft_error_void(ERROR_ALLOC));
	if ((path = ft_help_strjoin(path, ".help")) == NULL)
		return (ft_error_void(ERROR_ALLOC));
	return (path);
}

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

char		ft_help(char **av, char **env)
{
	char	**argv;
	pid_t	child;

	if (av[1] && ft_help_check(av[1]) == FALSE)
		return (ft_error_int(ERROR_BUILTIN, FALSE));
	if ((argv = ft_help_init_argv(ft_help_getname(av, env))) == NULL)
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
	return (TRUE);
}
