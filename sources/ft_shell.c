/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:39:19 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/12 08:09:11 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"
#include "terms.h"

static int	ft_launcher(t_sys **sys, char **str, int *exit)
{
	static size_t	n = 0;
	char			*tmp;

	ft_affprompt(++n, (*sys)->env);
	signal(SIGINT, &ft_sigint);
	if (ft_read(&(*str), &(*sys)) == FALSE)
	{
		signal(SIGINT, SIG_IGN);
		return (((*exit) = TRUE) - TRUE);
	}
	signal(SIGINT, SIG_IGN);
	if ((tmp = ft_strtrim(*str)) != NULL)
	{
		free(tmp);
		ft_check_parenthesis(&(*sys), &(*str), NULL, 0);
		if ((ft_history_maj(&((*sys)->history), *str, (*sys)->env)) == FALSE)
			ft_error(ERROR_HISTORY);
		else if ((tmp = ft_gestion_error(*str)) != NULL)
			ft_error(tmp);
		else if (((*sys)->cmds = ft_parsing(ft_strdup(*str), *sys)) == NULL)
			ft_error(ERROR_ALLOC);
		else
			return (TRUE);
	}
	return (FALSE);
}

static void	ft_shrc_launch(t_sys **sys, t_cmd *cmds)
{
	if ((ft_strcmp(cmds->name, "setenv") == 0) ||
		(ft_strcmp(cmds->name, "export") == 0))
		ft_setenv(cmds->argv[1], &((*sys)->env), FALSE);
	else if (ft_strcmp(cmds->name, "alias") == 0)
		ft_alias(cmds, &((*sys)->alias));
}

static int	ft_shrc_init(t_sys **sys, char *str, int fd)
{
	char	*tmp;
	char	*path;
	t_cmd	*cmds;

	(*sys)->alias = NULL;
	tmp = ft_getenv((*sys)->env, "HOME=");
	path = ft_strjoin(tmp, "/.42shrc");
	free(tmp);
	if (access(path, F_OK) != 0 || (fd = open(path, O_RDONLY)) == -1)
		return (FALSE);
	free(path);
	while (get_next_line(fd, &str) == 1)
	{
		if ((tmp = ft_gestion_error(str)) != NULL)
			ft_error(tmp);
		else if ((cmds = ft_parsecmd(str)) == NULL)
			ft_error(ERROR_ALLOC);
		else if (cmds)
			ft_shrc_launch(&(*sys), cmds);
		ft_free(&cmds, NULL, NULL);
	}
	ft_free(&cmds, &str, NULL);
	return (TRUE);
}

void		ft_shell(t_sys *sys, int exit, char *str, char *tmp)
{
	if (ft_history_init(&sys->history, sys->env) == FALSE)
		return (ft_error(ERROR_HISTORY));
	if (ft_shrc_init(&sys, NULL, 0) == FALSE)
		ft_error(ERROR_RC);
	while (exit == FALSE)
	{
		str = NULL;
		ft_termcaps_change(&sys->term_new);
		if (ft_launcher(&sys, &str, &exit) == TRUE)
		{
			ft_termcaps_change(&sys->term_save);
			if ((tmp = ft_exec(&sys, sys->cmds, NULL, 0)) != NULL)
			{
				if (ft_strcmp(tmp, EXIT) != 0)
					ft_error(tmp);
				else
					exit = TRUE;
			}
			ft_free(NULL, NULL, &(sys->cmds));
		}
	}
	ft_termcaps_change(&sys->term_save);
	ft_sys_free(sys);
}
