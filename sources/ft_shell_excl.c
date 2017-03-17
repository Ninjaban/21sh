/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_excl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:21:07 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/17 10:36:12 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static char	*ft_update_str(char *dest, char *str)
{
	char	*res;

	res = NULL;
	if (!dest)
		return (ft_strdup(str));
	if (str)
		res = ft_strjoin(dest, str);
	free(dest);
	return (res);
}

static void	ft_check_next(char **s)
{
	if (**s == '?' || **s == '{')
	{
		(*s)++;
		if (*(*s - 1) == '?')
			while (**s && **s != '?')
				(*s)++;
		else if (*(*s - 1) == '{')
			while (**s && **s != '}')
				(*s)++;
	}
	else if (ft_isdigit(**s) || (**s == '-' && ft_isdigit(*(*s + 1))))
	{
		(*s)++;
		while (**s && ft_isdigit(**s))
			(*s)++;
		(*s)--;
	}
	else
		while (**s && *(*s + 1) && *(*s + 1) != ' '
				&& *(*s + 1) != '\t' && *(*s + 1) != '\n'
				&& *(*s + 1) != '=' && *(*s + 1) != '(')
			(*s)++;
}

static char	*ft_check_cmd(t_sys **sys, char *s)
{
	char	*cmd;

	cmd = NULL;
	if (*s == '!')
		cmd = ft_hist_last((*sys)->history);
	else if (ft_isdigit(*s) || (*s == '-' && ft_isdigit(*(s + 1))))
		cmd = ft_hist_id((*sys)->history, s);
	else
		cmd = ft_hist_find((*sys)->history, ft_hist_str(s));
	return (cmd);
}

static void	ft_check_excl_norme(t_sys **sys, char **s, char **st, char **res)
{
	char	*cmd;

	cmd = NULL;
	if (**s == 0x5c && *(*s + 1) && *(*s + 1) == '!')
	{
		**s = '\0';
		*res = ft_update_str(*res, *st);
		*res = ft_update_str(*res, "!");
		(*s)++;
		*st = *s + 1;
	}
	else if (**s == '!' && *(*s + 1) && *(*s + 1) != ' ' && *(*s + 1) != '\t'
			&& *(*s + 1) != '\n' && *(*s + 1) != '=' && *(*s + 1) != '(')
	{
		**s = '\0';
		*res = ft_update_str(*res, *st);
		(*s)++;
		cmd = ft_check_cmd(sys, *s);
		ft_check_next(s);
		if (cmd)
			*res = ft_update_str(*res, cmd);
		*st = *s + 1;
	}
	(*s)++;
}

void		ft_check_excl(t_sys **sys, char **str)
{
	char	*s;
	char	*st;
	char	*res;

	s = *str;
	st = *str;
	res = ft_update_str(NULL, "\0");
	while (*s)
		ft_check_excl_norme(sys, &s, &st, &res);
	res = ft_update_str(res, st);
	if (ft_strcmp(*str, res) != 0)
		ft_log(TYPE_INFO, res);
	free(*str);
	*str = res;
}
