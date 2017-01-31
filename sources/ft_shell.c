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

/*
static void	ft_free(t_cmd **cmds, char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	if (cmds && *cmds)
	{
		free((*cmds)->name);
		ft_free_tab((*cmds)->argv);
		*cmds = NULL;
	}
}
*/
static char	ft_parse_parenthesis_open(char *str, char type)
{
	size_t		n;

	n = 0;
	while (str[n] && str[n] != ((type == 0) ? '\"' : '\''))
		n = n + 1;
	if (str[n] != ((type == 0) ? '\"' : '\''))
		return (FALSE);
	str[n] = (type == 0) ? '\a' : '\t';
	return (TRUE);
}

static void	ft_check_parenthesis(t_sys **sys, char **str)
{
	size_t		n;
	char		*tmp;
	char		*new;

	n = 0;
	while ((*str)[n])
	{
		if ((((*str)[n] == '\"' || (*str)[n] == '\'')) &&
			((ft_parse_parenthesis_open((*str) + n + 1,
				((*str)[n] == '\"') ? 0 : 1) == FALSE)))
		{
			ft_putstr("<quotes>\n");
			if (ft_read(&tmp, &(*sys)) == FALSE)
				ft_error(ERROR_READ);
			new = ft_strjoin(((*str)[n] == '\"') ? "'\\n'" : "\\n", tmp);
			free(tmp);
			tmp = ft_strjoin(*str, new);
			free(new);
			free(*str);
			*str = tmp;
		}
		else
			n = n + 1;
	}
	n = 0;
	while ((*str)[++n])
		if ((*str)[n] == '\a' || (*str)[n] == '\t')
			(*str)[n] = ((*str)[n] == '\a') ? '\"' : '\'';
}

static int	ft_launcher(t_sys **sys, char **str)
{
	static size_t	n = 0;
	char			*tmp;

	ft_affprompt(++n, (*sys)->env);
	if (ft_read(&(*str), &(*sys)) == FALSE)
		ft_error(ERROR_READ);
	if ((tmp = ft_strtrim(*str)) != NULL)
	{
		free(tmp);
		ft_check_parenthesis(&(*sys), &(*str));
		if ((ft_history_maj(&((*sys)->history), *str, (*sys)->env)) == FALSE)
			ft_error(ERROR_HISTORY);
		else if ((tmp = ft_gestion_error(*str)) != NULL)
			ft_error(tmp);
		else if (((*sys)->cmds = ft_parsing(*str, *sys)) == NULL)
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
//		ft_free(&cmds, &str);
	}
//	ft_free(&cmds, &str);
	return (TRUE);
}

void		ft_shell(t_sys *sys, int exit)
{
	char	*str;
	char	*tmp;

	if (ft_history_init(&sys->history, sys->env) == FALSE)
	{
		ft_error(ERROR_HISTORY);
		return ;
	}
	if (ft_shrc_init(&sys, NULL, 0) == FALSE)
		ft_error(ERROR_RC);
	while (exit == FALSE)
	{
		str = NULL;
		ft_termcaps_change(&sys->term_new);
		if (ft_launcher(&sys, &str) == TRUE)
		{
			ft_termcaps_change(&sys->term_save);
			if ((tmp = ft_exec(&sys)) != NULL)
			{
				if (ft_strcmp(tmp, EXIT) != 0)
					ft_error(tmp);
				else
					exit = TRUE;
			}
		}
//		ft_free(&(sys->cmds), &str);
	}
	ft_sys_free(sys);
}