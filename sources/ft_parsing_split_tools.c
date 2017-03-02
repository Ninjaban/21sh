/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_split_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 10:12:40 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/02 14:00:03 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_c(char c)
{
	size_t	n;
	char	*check;

	n = 0;
	check = ";|&";
	while (check[n] && check[n] != c)
		n = n + 1;
	if (check[n] && check[n] == c)
	{
		if (n == 0)
			return (1);
		return (2);
	}
	return (0);
}

static void	count_word_norme(char const *s, int *n, int *word)
{
	while (s[*n] && check_c(s[*n]) == 0)
	{
		*n = *n + 1;
		if (s[*n] && check_c(s[*n]) == 2)
		{
			if (s[*n + 1] && check_c(s[*n + 1]) == 2)
			{
				if (!(s[*n + 2]) || (s[*n + 2] && check_c(s[*n + 2]) == 0))
					*word = *word + 1;
				else
					*n = *n + 2;
			}
			else
				*n = *n + 1;
		}
	}
}

int			ft_parsing_count_word(char const *s)
{
	int		n;
	int		word;

	n = 0;
	word = 0;
	while (check_c(s[n]) == 1 && s[n])
		n = n + 1;
	while (s[n])
	{
		if (check_c(s[n]) == 1 && s[n])
		{
			word = word + 1;
			while (check_c(s[n]) == 1 && s[n])
				n = n + 1;
		}
		word = word + 1;
		count_word_norme(s, &n, &word);
		if (s[n] && check_c(s[n]) == 2)
		{
			while (s[n] && check_c(s[n]) == 2)
				n = n + 1;
		}
	}
	return (word);
}
