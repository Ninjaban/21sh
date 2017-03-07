/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:27:24 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/20 13:10:03 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	count_blank_start(char const *s)
{
	unsigned int	n;

	n = 0;
	while (*(s + n) == ' '
			|| *(s + n) == '\n'
			|| *(s + n) == '\t')
		n++;
	return (n);
}

unsigned int	count_blank_end(char const *s)
{
	unsigned int	i;
	unsigned int	n;

	i = ft_strlen(s) - 1;
	n = 0;
	while (*(s + i - n) == ' '
			|| *(s + i - n) == '\n'
			|| *(s + i - n) == '\t')
		n++;
	return (n);
}

char			*ft_strtrim(char const *s)
{
	char			*str;
	unsigned int	n_st;
	unsigned int	size;

	if (s)
	{
		n_st = count_blank_start(s);
		if (n_st == ft_strlen(s))
			size = 1;
		else
			size = ft_strlen(s) - (n_st + count_blank_end(s)) + 1;
		if ((str = (char *)malloc(sizeof(char) * (size))) == NULL)
			return (NULL);
		str = ft_strncpy(str, s + n_st, size - 1);
		*(str + size - 1) = '\0';
		return (str);
	}
	return (NULL);
}
