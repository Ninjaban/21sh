/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 21:13:50 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/30 13:52:48 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_esc.h"
#include "shell.h"
#include "error.h"

static char	ft_echo_unescape(char c)
{
	int	n;

	n = -1;
	while (++n < ANSI_MAX)
	{
		if (c == ANSI_LIST[n])
			return (ANSI_C_CHAR[n]);
	}
	return (c);
}

static void	ft_echo_token(char *str, char *token, size_t len)
{
	size_t	i;
	size_t	n;

	n = -1;
	i = -1;
	while (str[++n] && ++i < len)
	{
		if (IS_ESC(str[n]))
		{
			token[i] = 0x5c;
			i++;
			token[i] = ft_echo_unescape(str[n]);
			n++;
		}
		else
			token[i] = str[n];
		ft_log(TYPE_INFO, token);
	}
	token[len] = '\0';
}

static void	ft_echo_putstr(char *str)
{
	char	*token;
	size_t	n;
	size_t	len;
	size_t	count;

	if (!str)
		return ;
	len = ft_strlen(str);
	count = 0;
	n = -1;
	while (str[++n])
		if (IS_ESC(str[n]))
		{
			count++;
			n++;
		}
	if ((token = ft_strnew(len + count)) == NULL)
		return (ft_putstr(str));
	ft_echo_token(str, token, len + count);
	ft_putstr(token);
	free(token);
}

int			ft_echo(char **argv)
{
	size_t	n;

	n = 1;
	while (argv[n])
	{
		ft_echo_putstr(argv[n]);
		if (argv[++n])
			ft_putstr(" ");
	}
	ft_putstr("\n");
	return (TRUE);
}
