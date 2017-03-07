/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:14:38 by mrajaona          #+#    #+#             */
/*   Updated: 2016/12/22 12:03:17 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			free_tab(char **tab, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static unsigned int	count_wd(char const *s, char c)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	i = 0;
	while (*(s + i))
	{
		while (*(s + i) == c)
			i++;
		if (*(s + i))
		{
			count++;
			while (*(s + i) && *(s + i) != c)
				i++;
		}
	}
	return (count);
}

static char			*new_word(char const *s, char c)
{
	char			*wd;
	size_t			size;

	size = 0;
	while (*(s + size) && *(s + size) != c)
		size++;
	if ((wd = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	wd = ft_strncpy(wd, s, size);
	*(wd + size) = '\0';
	return (wd);
}

static char			**fill_tab(char const *s, char c, char **tab,
								unsigned int size)
{
	unsigned int	n_tab;
	unsigned int	n_s;

	n_tab = 0;
	n_s = 0;
	while (n_tab < size)
	{
		while (*(s + n_s) && *(s + n_s) == c)
			n_s++;
		if ((tab[n_tab] = new_word(s + n_s, c)) == NULL)
		{
			free_tab(tab, size);
			return (NULL);
		}
		while (*(s + n_s) && *(s + n_s) != c)
			n_s++;
		n_tab++;
	}
	return (tab);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**tab;
	unsigned int	nb_wd;

	if (s)
	{
		nb_wd = count_wd(s, c);
		if ((tab = (char **)malloc(sizeof(char *) * (nb_wd + 1))) == NULL)
			return (NULL);
		tab[nb_wd] = NULL;
		return (fill_tab(s, c, tab, nb_wd));
	}
	return (NULL);
}
