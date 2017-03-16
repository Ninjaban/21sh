/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hist_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 12:31:35 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/16 13:06:52 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

static char	*ft_hist_str_qmark(char *str)
{
	char	*res;
	size_t	len;
	size_t	i;

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
	return (res);
}

static char	*ft_hist_str_brace(char *str)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = 1;
	while (str[len] && str[len] != '}')
		len++;
	if ((res = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (ft_error_void(ERROR_ALLOC));
	i = 0;
	while (i < len)
	{
		if (str[len] && (str[len] == ' ' || str[len] != '\t'
							|| str[len] != '\n' || str[len] != '='
							|| str[len] != '('))
		{
			free(res);
			return (ft_error_void(ERROR_HIST_SYNTAX));
		}
		res[i] = str[i + 1];
		i++;
	}
	res[len - 1] = '?';
	res[len] = '\0';
	return (res);
}

static char	*ft_hist_str_default(char *str)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t'
			&& str[len] != '\n' && str[len] != '=' && str[len] != '(')
		len++;
	if ((res = (char *)malloc(sizeof(char) * (len + 2))) == NULL)
		return (ft_error_void(ERROR_ALLOC));
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[len] = '?';
	res[len + 1] = '\0';
	return (res);
}

char		*ft_hist_str(char *str)
{
	char	*res;

	res = NULL;
	if (*str == '?')
		res = ft_hist_str_qmark(str);
	else if (*str == '{')
		res = ft_hist_str_brace(str);
	else
		res = ft_hist_str_default(str);
	return (res);
}
