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


static void	ft_shrc_launch(t_sys **sys, char *str)
{
    char    *tmp;
    t_cmd   *cmds;

    if ((tmp = ft_gestion_error(str)) != NULL)
        ft_log(TYPE_WARNING, tmp);
    else if ((cmds = ft_parsecmd(str)) == NULL)
        ft_log(TYPE_ERROR, ERROR_ALLOC);
    else if (ft_strcmp(cmds->name, "setenv") == 0)
        ft_setenv(cmds->argv[1], &((*sys)->env), NULL, FALSE);
    else if (ft_strcmp(cmds->name, "alias") == 0)
        ft_alias(cmds, &((*sys)->alias));
    ft_free(&cmds, NULL, NULL);
}

int	        ft_shrc_init(t_sys **sys, char *str, int fd)
{
    char	*tmp;
    char	*path;

    (*sys)->alias = NULL;
    tmp = ft_getenv((*sys)->env, "HOME=");
    path = ft_strjoin(tmp, "/.42shrc");
    free(tmp);
    if (access(path, F_OK) != 0 || (fd = open(path, O_RDONLY)) == -1)
    {
        free(path);
        return (FALSE);
    }
    free(path);
    while (get_next_line(fd, &str) == 1)
    {
        if ((tmp = ft_strtrim(str)) != NULL)
        {
            free(tmp);
            ft_shrc_launch(&(*sys), str);
        }
    }
    free(str);
    return (TRUE);
}
