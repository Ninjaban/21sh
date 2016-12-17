/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:39:19 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/17 13:32:14 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"
#include "terms.h"

/*
static void	ft_free(t_cmd ***cmds, char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	if (cmds && *cmds)
	{
		ft_free_cmds(*cmds);
		*cmds = NULL;
	}
}
*/
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
		if ((ft_history_maj(&((*sys)->history), *str,(*sys)->env)) == FALSE)
			ft_error(ERROR_HISTORY);
		else if ((tmp = ft_gestion_error(*str)) != NULL)
			ft_error(tmp);
		else
			ft_parsing(*str, *sys);
	}
	/*
	(*sys)->cmds = NULL;
	*str = NULL;
	if (get_next_line(0, &(*str)) == -1)
		ft_error(ERROR_READ);
	else if ((ft_history_maj(&((*sys)->history), *str, (*sys)->env)) == FALSE)
		ft_error(ERROR_ALLOC);
	else if (((*sys)->cmds = ft_parsing(*str, *sys, 0)) == NULL)
		ft_error(ERROR_ALLOC);
	else if ((tmp = ft_gestion_error((*sys)->cmds)) != NULL)
		ft_error(tmp);
	else
		return (TRUE);
	*/
	return (FALSE);
}
/*
static void	ft_shrc_launch(t_sys **sys)
{
	if ((ft_strcmp((*sys)->cmds[0]->name, "setenv") == 0) ||
		(ft_strcmp((*sys)->cmds[0]->name, "export") == 0))
		ft_setenv((*sys)->cmds[0]->argv[1], &((*sys)->env), FALSE);
	else if (ft_strcmp((*sys)->cmds[0]->name, "alias") == 0)
		ft_alias((*sys)->cmds[0], &((*sys)->alias));
}

static int	ft_shrc_init(t_sys **sys, char *str, int fd)
{
	char	*tmp;
	char	*path;

	(*sys)->alias = NULL;
	tmp = ft_getenv((*sys)->env, "HOME");
	path = ft_strjoin(tmp, "/.42shrc");
	free(tmp);
	if ((fd = open(path, O_RDWR | O_CREAT, 0640)) == -1)
		return (FALSE);
	free(path);
	while (get_next_line(fd, &str) == 1)
	{
		if ((ft_history_maj(&((*sys)->history), str, (*sys)->env)) == FALSE)
			ft_error(ERROR_ALLOC);
		else if (((*sys)->cmds = ft_parsing(str, *sys, 0)) == NULL)
			ft_error(ERROR_ALLOC);
		else if ((tmp = ft_gestion_error((*sys)->cmds)) != NULL)
			ft_error(tmp);
		else if ((*sys)->cmds[0])
		ft_shrc_launch(&(*sys));
		ft_free(&((*sys)->cmds), &str);
	}
	ft_free(&((*sys)->cmds), &str);
	return (TRUE);
}
*/
void		ft_shell(t_sys *sys, int exit)
{
	char	*str;
/*	char	*tmp;*/

	if (ft_history_init(&sys->history, sys->env) == FALSE)
	{
		ft_error(ERROR_HISTORY);
		return ;
	}
/*	if (ft_shrc_init(&sys, NULL, 0) == FALSE)
	ft_error(ERROR_RC);*/
	while (exit == FALSE)
	{
		ft_termcaps_change(&sys->term_new);
		ft_launcher(&sys, &str);
/*		if (ft_launcher(&sys, &str) == TRUE)
		{
		ft_termcaps_change(&sys->term_save);
			if ((tmp = ft_exec(&sys)) != NULL)
			{
				if (ft_strcmp(tmp, EXIT) != 0)
					ft_error(tmp);
				else
					exit = TRUE;
					}
}*/
/*		ft_free(&(sys->cmds), &str);*/
	}
}
