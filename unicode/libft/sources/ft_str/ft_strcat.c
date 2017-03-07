/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:10:14 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/09 10:56:00 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *s1, const char *s2)
{
	char			*tmp;
	unsigned int	i;

	if (!s1 && !s2)
		return (s1);
	tmp = s1;
	while (*tmp)
		tmp++;
	i = 0;
	while (s2[i])
	{
		tmp[i] = s2[i];
		i++;
	}
	tmp[i] = '\0';
	return (s1);
}