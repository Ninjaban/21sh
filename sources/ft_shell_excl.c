/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_excl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:21:07 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/15 13:20:50 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

/*
** search s2 in s1
*/

int	ft_hist_match(char *s1, char *s2)
{
	if (!(*s1) && !(*s2))
		return (1);
	else if (*s1 == *s2)
	{
		if (*(s1) == '?')
			return (ft_hist_match(s1 + 1, s2) || ft_hist_match(s1, s2 + 1));
		else
			return (ft_hist_match(s1 + 1, s2 + 1));
	}
	else if (*s2 == '?')
	{
		if (!*s1)
			return (ft_hist_match(s1, s2 + 1));
		else
			return (ft_hist_match(s1 + 1, s2) || ft_hist_match(s1, s2 + 1));
	}
	return (0);
}

static char	*ft_hist_str(char *str)
{
	char	*res;
	size_t	len;
	size_t	i;

	if (*str == '!')
		return (NULL);
	res = NULL;

	if (*str == '?')
	{
		len = 1;
		while (str[len] && str[len] != '?')
			len++;
		if ((res = (char *)malloc(sizeof(char) * (len + 2))) == NULL)
			return (ft_error_void(ERROR_ALLOC));
		i = 0;
		while (i <= len)
		{
			res[i] = str[i];
			i++;
		}
		res[len + 1] = '\0';
	}
	else if (*str == '{') // verifier le comportement original
	{
		len = 1;
		while (str[len] && str[len] != '}')
			len++;
		if ((res = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
			return (ft_error_void(ERROR_ALLOC));
		i = 0;
		while (i < len)
		{
			res[i] = str[i + 1];
			i++;
		}
		res[len - 1] = '?';
		res[len] = '\0';
	}
	else
	{
		len = 0;
		while (str[len] && str[len] != ' ' && str[len] != '\t'
				&& str[len] != '\n' && str[len] != '=' && str[len] != '(')
			len++;
		if ((res = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
			return (ft_error_void(ERROR_ALLOC));
		i = 0;
		while (i < len)
		{
			res[i] = str[i + 1];
			i++;
		}
		res[len - 1] = '?';
		res[len] = '\0';
	}

	ft_log(TYPE_INFO, res);
	return (res);
}

static char	*ft_hist_last(t_lst *history)
{
	t_lst	*tmp;

	tmp = history;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp ? ((t_hist *)(tmp->data))->line : NULL);
}

static char	*ft_hist_find(t_lst *history, char *str)
{
	t_lst	*tmp;
	char	*res;

	if (!str)
		return (NULL);
	tmp = history;
	res = NULL;
	while (tmp)
	{
		if (ft_hist_match(((t_hist *)(tmp->data))->line, str) == 1)
			res = ((t_hist *)(tmp->data))->line;
		tmp = tmp->next;
	}
	free(str);
	return (res);
}

static char	*ft_hist_id(t_lst *history, char *str)
{
	t_lst	*tmp;
	int		id;

	id = ft_atoi(str);
	tmp = history;
	if (id > 0 && id < ((t_hist *)(tmp->data))->id)
		return (NULL);
	if (id < 0)
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		id = ((t_hist *)(tmp->data))->id + 1 + id;
		tmp = history;
	}
	if (id < ((t_hist *)(tmp->data))->id)
		return (NULL);
	while (tmp)
	{
		if (id == ((t_hist *)(tmp->data))->id)
			return (((t_hist *)(tmp->data))->line);
		tmp = tmp->next;
	}
	return (NULL);
}


static char	*ft_update_str(char *dest, char *str)
{
	char	*res;

	res = NULL;
	if (!dest)
		return (ft_strdup(str));
	if (str)
		res = ft_strjoin(dest, str);
	if (dest)
		free(dest);
	return (res);
}

void	ft_check_excl(t_sys **sys, char **str)
{
	char	*s;
	char	*st;
	char	*cmd;
	char	*res;

	ft_log(TYPE_WARNING, "START");
	s = *str;
	st = *str;
	res = ft_update_str(NULL, "\0");
	while (*s)
	{
		cmd = NULL;
		if (*s == '!'&& *(s + 1) && *(s + 1) != ' ' && *(s + 1) != '\t'
			&& *(s + 1) != '\n' && *(s + 1) != '=' && *(s + 1) != '(')
		{
			*s = '\0';
			res = ft_update_str(res, st);
			s++;
			if (*s == '!')
				cmd = ft_hist_last((*sys)->history);
			else if (*s == '?')
				cmd = ft_hist_find((*sys)->history, ft_hist_str(s));
			else if (*s == '{')
				cmd = ft_hist_find((*sys)->history, ft_hist_str(s));
			else if (ft_isdigit(*s) || (*s == '-' && ft_isdigit(*(s + 1))))
				cmd = ft_hist_id((*sys)->history, s);
			else
				cmd = ft_hist_find((*sys)->history, ft_hist_str(s));
			if (*s == '?' || *s == '{')
			{
				s++;
				if (*(s - 1) == '?')
					while (*s && *s != '?')
						s++;
				else if (*(s - 1) == '{')
					while (*s && *s != '}')
						s++;
			}
			else if (ft_isdigit(*s) || (*s == '-' && ft_isdigit(*(s + 1))))
			{
				s++;
				while (*(s + 1) && ft_isdigit(*(s + 1)))
					s++;
			}
			else
				while (*s && *(s + 1) && *(s + 1) != ' ' && *(s + 1) != '\t'
					   && *(s + 1) != '\n' && *(s + 1) != '=' && *(s + 1) != '(')
					s++;
		}

		else if (*s == '^')
			;

		s++;
		if (cmd)
		{
			res = ft_update_str(res, cmd);
			st = s;
		}

	}
	res = ft_update_str(res, st);
	free(*str);
	*str = res;
	ft_log(TYPE_WARNING, "END");
}
