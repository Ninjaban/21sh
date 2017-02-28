/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2017/02/24 10:55:43 by mrajaona         ###   ########.fr       */
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
	ft_putendl(str + n);
	ft_init_node(&(*cmds), str + n, ft_get_redir_fd(str, n));
}

static void		ft_add_node(t_btree **cmds, char **tab, int n)
{
	char	node;

	node = FALSE;
	if (tab[n])
	{
		if (ft_strcmp(tab[n], ";") == 0 || ft_strcmp(tab[n], "&&") == 0
			|| ft_strcmp(tab[n], "||") == 0)
		{
			if (ft_strcmp(tab[n], ";") == 0)
				node = CMD;
			else if (ft_strcmp(tab[n], "&&") == 0)
				node = AND;
			else if (ft_strcmp(tab[n], "||") == 0)
				node = OR;
			btree_add_node(&(*cmds), btree_create_node(
					ft_new_node(node, NULL, FALSE, FALSE)), &ft_false_node);
			ft_add_node(&(*cmds), tab, n + 1);
		}
		else
		{
//			ft_tild_file(&(tab[n]), '\a', ';'); // A verifier pour les && et les || dans les ""
			ft_parsing_multicmd(&(*cmds), tab[n]);
			ft_add_node(&(*cmds), tab, n + 1);
		}
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
	if ((tab = ft_parsing_split(tmp)) == NULL)
	{
		free(str);
		free(tmp);
		return (NULL);
	}
	free(str);
	free(tmp);
	cmds = btree_create_node(ft_new_node(CMD, NULL, FALSE, FALSE));

	for (int i = 0 ; tab[i] ; ++i)
		ft_putendl(tab[i]);

	ft_add_node(&cmds, tab, 0);
	ft_free_tab(tab);
	return (cmds);
}

// A enlever
void			ft_display(void *root)
{
	t_node		*node;

	if ((node = ((t_btree *)root)->item))
	{
		if (!node->node)
			ft_putstr(" NULL ");
		else if (node->node == CMD)
			ft_putstr(" ; ");
		else if (node->node == AND)
			ft_putstr(" && ");
		else if (node->node == OR)
			ft_putstr(" || ");
		else if (node->redir != FALSE)
		{
			if (node->redir == PIPE)
				ft_putstr(" | ");
			else if (node->redir == REDIR_R)
				ft_putstr(" > ");
			else if (node->redir == REDIR_L)
				ft_putstr(" < ");
			else if (node->redir == CONCAT_R)
				ft_putstr(" >> ");
			else if (node->redir == CONCAT_L)
				ft_putstr(" << ");
		}
		else if (node->redir == FALSE && node->cmd)
			for (int n = 0; node->cmd->argv[n]; ++n)
				ft_putstr(node->cmd->argv[n]);
	}
}

t_btree			*ft_parsing(char *str, t_sys *sys)
{
	t_btree		*cmds;

	if (!str)
		return (NULL);
	cmds = ft_parsing_line(str, sys);
	btree_apply_prefix(cmds, &ft_display); // A enlever
	ft_putendl(""); // A enlever
	return (cmds);
}
