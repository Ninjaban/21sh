/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2017/02/17 11:58:54 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void		ft_parsing_multicmd(t_btree **cmds, char *str)
{
	size_t		n;
	char		change;

	n = ft_strlen(str);
	change = TRUE;
	while (n > 0)
	{
		if (str[n] == '\"' || str[n] == '\'')
			change = (change == TRUE) ? FALSE : TRUE;
		if (change == TRUE && (str[n] == '|' || str[n] == '<' || str[n] == '>'))
		{
			if (n > 0 && (str[n - 1] == '<' || str[n - 1] == '>'))
				n = n - 1;
			ft_init_node(&(*cmds), str + n, ft_get_redir_fd(str, n));
			n = n - 1;
			while (n > 0 && ft_isdigit(str[n]))
				n = n - 1;
			str[++n] = '\0';
		}
		n = n - 1;
	}
	ft_init_node(&(*cmds), str + n, ft_get_redir_fd(str, n));
}

static void		ft_add_node(t_btree **cmds, char **tab, char redir, int n)
{
	if (tab[n])
	{
		if (n > 0)
			btree_add_node(&(*cmds), btree_create_node(
					ft_new_node(FALSE, NULL, redir, FALSE)), &ft_false_node);
		ft_tild_file(&(tab[n]), '\a', ';');
		ft_parsing_multicmd(&(*cmds), tab[n]);
		ft_add_node(&(*cmds), tab, redir, n + 1);
	}
}

void			ft_parsing_alias(char **str, t_sys *sys)
{
	size_t		n;
	char		change;
	int			nb;

	n = 0;
	change = TRUE;
	while ((*str)[n])
	{
		if ((*str)[n] == '\"' || (*str)[n] == '\'')
		{
			change = (change == TRUE) ? FALSE : TRUE;
			n = n + 1;
		}
		nb = 0;
		if (change == TRUE)
			nb = ft_check_alias(&(*str), sys->alias, n);
		if (nb != 0)
			n = n + nb;
		else
			while ((*str)[n] && (*str)[n] != ' ' && (*str)[n] != '\n' &&
					(*str)[n] != '\"' && (*str)[n] != '\'')
				n = n + 1;
		while ((*str)[n] && ((*str)[n] == ' ' || (*str)[n] == '\n'))
			n = n + 1;
	}
}

t_btree			*ft_parsing_line(char *str, t_sys *sys)
{
	t_btree		*cmds;
	char		**tab;
	char		*tmp;

	tmp = ft_tild(ft_varenv(str, sys->env, TRUE), sys->env);
	ft_parsing_alias(&tmp, sys);
	ft_tild_file(&tmp, ';', '\a');
	if ((tab = ft_parsing_split(tmp, ";|&")) == NULL)
	{
		free(str);
		free(tmp);
		return (NULL);
	}
	free(str);
	free(tmp);

	int n = 0;
	while (tab[n])
	{
		ft_putendl(tab[n]);
		n++;
	}

	cmds = btree_create_node(ft_new_node(FALSE, NULL, FALSE, FALSE));
	ft_add_node(&cmds, tab, CMD, 0);
	ft_free_tab(tab);
	return (cmds);
}

t_btree			*ft_parsing(char *str, t_sys *sys)
{
	t_btree		*cmds;

	if (!str)
		return (NULL);
	cmds = ft_parsing_line(str, sys);
	return (cmds);
}
