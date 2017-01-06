/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 09:00:25 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/06 11:42:39 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_find(char *str, char *to_find, int n, int j)
{
	int	i;

	if (to_find[0] == '\0')
		return (n);
	while (str[n] != '\0')
	{
		i = 0;
		while (str[n + i] == to_find[j + i] && str[n + i] != '\0' &&
				(to_find[j + i] != '\0' && to_find[j + i] != '*'))
			i = i + 1;
		if (to_find[j + i] == '\0' || to_find[j + i] == '*')
			return (n + i);
		n = n + 1;
	}
	return (-1);
}

static int	ft_comp(char *str, char *src, int n, int i)
{
	while (str[n] != '\0' && (src[i] != '\0' && src[i] != '*'))
	{
		if (str[n] != src[i])
			return (-1);
		n = n + 1;
		i = i + 1;
	}
	if (src[i] == '*')
		return (n);
	if (src[i] == '\0' && str[n] == '\0')
		return (n);
	return (-1);
}

static int	ft_match(char *s1, char *s2, int n, int i)
{
	while (s1[n] != '\0' && s2[i] != '\0')
	{
		if (s2[i] == '*')
			i = i + 1;
		if (s2[i] == '\0')
			return (1);
		if (s2[i] != '*')
		{
			if (i > 0 && s2[i - 1] == '*')
			{
				if ((n = ft_find(s1, s2, n, i)) == -1)
					return (0);
			}
			else if ((n = ft_comp(s1, s2, n, i)) == -1)
				return (0);
			while (s2[i] != '\0' && s2[i] != '*')
				i = i + 1;
		}
	}
	if (s1[n] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}

int		match(char *s1, char *s2)
{
	if (ft_match(s1, s2, 0, 0) == 1)
		return (1);
	return (0);
}
