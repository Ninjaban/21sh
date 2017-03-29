/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:39:19 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/21 10:53:08 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"
#include "terms.h"

static char	ft_launcher_parse(char **str, t_sys **sys)
{
	char	*tmp;

	ft_check_parenthesis(&(*sys), &(*str), NULL);
	ft_check_excl(&(*sys), &(*str));
	if ((ft_history_maj(&((*sys)->history), *str, (*sys)->env)) == FALSE)
		ft_log(TYPE_WARNING, ERROR_HISTORY);
	else if ((tmp = ft_gestion_error(*str)) != NULL)
		ft_log(TYPE_ERROR, tmp);
	else if (((*sys)->cmds = ft_parsing(ft_strdup(*str), *sys)) == NULL)
		ft_log(TYPE_ERROR, ERROR_ALLOC);
	else
		return (TRUE);
	return (FALSE);
}

static char	ft_launcher(t_sys **sys, char **str, int *exit)
{
	static size_t	n = 0;
	char			*tmp;

	ft_affprompt(++n, (*sys)->env);
	signal(SIGINT, &ft_sigint);
	if (ft_read(&(*str), &(*sys), n, FALSE) == FALSE)
	{
		signal(SIGINT, SIG_IGN);
		return (((*exit) = TRUE) - TRUE);
	}
	signal(SIGINT, SIG_IGN);
	if ((tmp = ft_strtrim(*str)) != NULL)
	{
		free(tmp);
		if (ft_launcher_parse(&(*str), &(*sys)) == TRUE)
			return (TRUE);
	}
	else
		n = n - 1;
	return (FALSE);
}

static char	ft_shell_init(t_sys **sys)
{
	if (ft_history_init(&(*sys)->history, (*sys)->env) == FALSE)
		return ((char)ft_error_int(ERROR_HISTORY, FALSE));
	if (((*sys)->keymap = ft_keymap_init()) == NULL)
		return ((char)ft_error_int(ERROR_KEYMAP, FALSE));
	if (ft_shrc_init(&(*sys), NULL, 0) == FALSE)
		ft_log(TYPE_WARNING, ERROR_RC);
	return (TRUE);
}

void		ft_shell(t_sys *sys, int exit, char *str, char *tmp)
{
	if (ft_shell_init(&sys) == FALSE)
		return ;
	while (exit == FALSE)
	{
		str = NULL;
		ft_termcaps_change(&sys->term_new);
		if (ft_launcher(&sys, &str, &exit) == TRUE)
		{
			ft_termcaps_change(&sys->term_save);
			signal(SIGTSTP, SIG_DFL);
			if ((tmp = ft_exec(&sys, sys->cmds, NULL)) != NULL)
			{
				if (ft_strcmp(tmp, EXIT) != 0)
					ft_log(TYPE_WARNING, tmp);
				else
					exit = TRUE;
			}
			signal(SIGTSTP, SIG_IGN);
			ft_free(NULL, NULL, &(sys->cmds));
		}
		free(str);
	}
	ft_termcaps_change(&sys->term_save);
	ft_sys_free(sys);
}
