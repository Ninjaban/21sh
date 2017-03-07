/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 08:52:57 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/09 09:09:03 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_match(char *s1, char *s2)
{
	if (!(*s1) && !(*s2))
		return (1);
	else if (*s1 == *s2)
	{
		if (*(s1) == '*')
			return (ft_match(s1 + 1, s2) || ft_match(s1, s2 + 1));
		else
			return (ft_match(s1 + 1, s2 + 1));
	}
	else if (*s2 == '*')
	{
		if (!*s1)
			return (ft_match(s1, s2 + 1));
		else
			return (ft_match(s1 + 1, s2) || ft_match(s1, s2 + 1));
	}
	return (0);
}
