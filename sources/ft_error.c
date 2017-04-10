/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:22:04 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 09:24:05 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

void		ft_log(char type, char *log)
{
	char	*str;
	char	*tmp1;
	char	*tmp2;
	char	*print;

	if (type == TYPE_INFO)
		str = " [\033[36mINFO\033[0m]    : ";
	else if (type == TYPE_WARNING)
		str = " [\033[33mWARNING\033[0m] : ";
	else
		str = " [\033[31mERROR\033[0m]   : ";
	tmp1 = ft_strjoin(NAME, str);
	tmp2 = ft_strjoin(tmp1, log);
	print = ft_strjoin(tmp2, "\n");
	ft_putstr_fd(print, (type == TYPE_ERROR) ? 2 : 0);
	free(tmp1);
	free(tmp2);
	free(print);
}

void		*ft_error_void(char *error)
{
	char	*tmp1;
	char	*tmp2;
	char	*print;

	tmp1 = ft_strjoin(NAME, " [\033[31mERROR\033[0m]   : ");
	tmp2 = ft_strjoin(tmp1, error);
	print = ft_strjoin(tmp2, "\n");
	ft_putstr_fd(print, 2);
	free(tmp1);
	free(tmp2);
	free(print);
	return (NULL);
}

int			ft_error_int(char *error, int exit)
{
	char	*tmp1;
	char	*tmp2;
	char	*print;

	tmp1 = ft_strjoin(NAME, " [\033[31mERROR\033[0m]   : ");
	tmp2 = ft_strjoin(tmp1, error);
	print = ft_strjoin(tmp2, "\n");
	ft_putstr_fd(print, 2);
	free(tmp1);
	free(tmp2);
	free(print);
	return (exit);
}

void		ft_error(char *error)
{
	char *tmp1;
	char *tmp2;
	char *print;

	tmp1 = ft_strjoin(NAME, " [\033[31mERROR\033[0m]   : ");
	tmp2 = ft_strjoin(tmp1, error);
	print = ft_strjoin(tmp2, "\n");
	ft_putstr_fd(print, 2);
	free(tmp1);
	free(tmp2);
	free(print);
}

void		ft_cmd_nfound(char *name)
{
	char	*tmp1;
	char	*tmp2;
	char	*print;

	tmp1 = ft_strjoin(NAME, " [\033[31mERROR\033[0m]   : ");
	tmp2 = ft_strjoin(tmp1, name);
	print = ft_strjoin(tmp2, " -> Commande introuvable\n");
	ft_putstr_fd(print, 2);
	free(tmp1);
	free(tmp2);
	free(print);
}
