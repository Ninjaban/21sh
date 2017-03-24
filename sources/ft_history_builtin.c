/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:27:53 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/17 11:49:47 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"

static int	ft_isvalid_nb(char *str)
{
	while (*str && *str == '+')
		str++;
	while (*str && ft_isdigit(*str))
		str++;
	return (*str ? FALSE : TRUE);
}

/*
** Options :
** -h	1
** -r	2
** -hr	3
*/

static int	ft_chk_opt(char *str, char *opt)
{
	while (*str && *str == '-')
		str++;
	while (*str && (*str == 'h' || *str == 'r'))
	{
		*opt = *opt | (*str == 'h' ? 1 : 2);
		str++;
	}
	return (*str ? FALSE : TRUE);
}

static void	ft_hist_print(t_hist **tab, char opt, int m)
{
	if (opt & 2)
		while (--m > 0)
		{
			if (!(opt & 1))
			{
				ft_putnbr((tab[m])->id);
				ft_putstr("\t");
			}
			ft_putendl((tab[m])->line);
		}
	else
	{
		m = 0;
		while (tab[m] && tab[m + 1])
		{
			if (!(opt & 1))
			{
				ft_putnbr((tab[m])->id);
				ft_putstr("\t");
			}
			ft_putendl((tab[m])->line);
			m++;
		}
	}
}

static int	ft_hist_tools(t_lst **history, char opt, int n)
{
	int		m;
	int		size;
	t_hist	**tab;
	t_lst	*tmp;

	if ((tab = (t_hist **)malloc(sizeof(t_hist *) * (n + 1))) == NULL)
		return (ft_error_int(ERROR_ALLOC, FALSE));
	tmp = *history;
	if ((size = ft_list_size(*history)) > n)
		while (size > n)
		{
			tmp = tmp->next;
			size--;
		}
	m = 0;
	while (tmp && m < n)
	{
		tab[m] = (t_hist *)(tmp->data);
		tmp = tmp->next;
		m++;
	}
	tab[m] = NULL;
	ft_hist_print(tab, opt, m);
	free(tab);
	return (TRUE);
}

int			ft_hist_built(char **argv, t_lst **history)
{
	int		n;
	int		x;
	char	opt;

	x = 0;
	while (argv[++x] && argv[x][0] == '-')
		if (ft_chk_opt(argv[x], &opt) == FALSE)
			return (ft_error_int(ERROR_OPTION, FALSE));
	n = HISTORY_SIZE;
	if (argv[x])
	{
		if (argv[x + 1] || ft_isvalid_nb(argv[x]) == FALSE)
			return (ft_error_int(ERROR_SYNTAX, FALSE));
		else
			n = ft_atoi(argv[x]);
	}
	ft_hist_tools(history, opt, n + 1);
	return (TRUE);
}
