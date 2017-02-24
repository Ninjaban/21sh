/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:10:53 by mrajaona          #+#    #+#             */
/*   Updated: 2017/02/24 10:43:36 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

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

static int	size_word(char const *s, int n)
{
	int		len;

	len = 0;
	if (check_c(s[n]) == 0)
		while (s[n + len] && check_c(s[n + len]) == 0)
		{
			len = len + 1;
			if (s[n + len] && check_c(s[n + len]) == 2)
			{
				if (s[n + len + 1] && check_c(s[n + len + 1]) == 2)
				{
					if (!(s[n + len + 2]) || (s[n + len + 2]
											&& check_c(s[n + len + 2]) == 0))
						(void)n;
					else
						len = len + 2;
				}
				else
					len = len + 1;
			}
		}
	else
		while (s[n + len] && check_c(s[n + len]) != 0)
			len = len + 1;
	return (len);
}

static char	**complete_tab(char const *s, char **tab)
{
	int		n;
	int		i;
	int		j;
	int		size;

	n = 0;
	i = 0;
	while (s[n])
	{
		if (check_c(s[n]) == 1)
			size = 1;
		else
			size = size_word(s, n);
		if ((tab[i] = malloc(size + 1)) == NULL)
			return (NULL);
		j = 0;
		size += n;
		while (n < size)
			tab[i][j++] = s[n++];
		tab[i++][j] = '\0';
		if (check_c(s[n] == 1))
			while (s[n] && (check_c(s[n]) == 1 || s[n] == ' ' || s[n] == '\t'))
				n = n + 1;
	}
	return (tab);
}

char		**ft_parsing_split(char const *s)
{
	char	**tab;
	int		word;

	if (s == NULL)
		return (NULL);
	word = ft_parsing_count_word(s);
	if ((tab = malloc(sizeof(char *) * (word + 1))) == NULL)
		return (NULL);
	while (word >= 0)
		tab[word--] = NULL;
	if ((tab = complete_tab(s, tab)) == NULL)
		return (NULL);
	return (tab);
}
