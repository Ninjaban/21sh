/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/20 09:25:45 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static char		**ft_tabcpy(char **tab)
{
	char		**dst;
	int			n;

	n = -1;
	if ((dst = malloc(sizeof(char *) * (ft_tablen(tab) + 1))) == NULL)
		return (NULL);
	while (tab[++n])
		dst[n] = ft_strdup(tab[n]);
	dst[n] = NULL;
	return (dst);
}
/*
static char		*ft_parse_parenthesis(char *str, char c, char r)
{
	size_t		n;
	char		*tmp;
	int			open;

	n = 0;
	open = FALSE;
	while (str[n])
	{
		if (str[n] == '\"')
		{
			if ((tmp = ft_delchar(str, (n > 0 && str[n - 1] == '\\')
									? n - 1 : n)) == NULL)
				return (NULL);
			str = tmp;
			open = (open == TRUE) ? FALSE : TRUE;
		}
		if (open == TRUE && str[n] == c)
			str[n] = r;
		n = n + 1;
	}
	return (str);
}

static void		ft_parenthesis_undo(char ***tab)
{
	size_t		n;
	size_t		i;

	n = 0;
	while ((*tab) && (*tab)[n])
	{
		i = 0;
		while ((*tab)[n][i])
		{
			if ((*tab)[n][i] == '\a')
				(*tab)[n][i] = ' ';
			i = i + 1;
		}
		n = n + 1;
	}
}

static t_cmd	*ft_parsecmd(char *str, char *tmp, char **tab)
{
	t_cmd		*cmd;

	if ((tmp = ft_parse_parenthesis(ft_strdup(str), ' ', '\a')) == NULL)
		return (NULL);
	if ((tab = ft_strsplit(tmp, " \t\n")) == NULL || !tab[0])
		return (NULL);
	free(tmp);
	if ((cmd = malloc(sizeof(t_cmd))) == NULL)
	{
		ft_free_tab(tab);
		return (NULL);
	}
	cmd->name = NULL;
	cmd->argv = NULL;
	ft_parenthesis_undo(&tab);
	if ((cmd->name = ft_strdup(tab[0])) == NULL)
	{
		ft_free_tab(tab);
		free(cmd);
		return (NULL);
	}
	cmd->argv = ft_tabcpy(tab);
	ft_free_tab(tab);
	free(str);
	return (cmd);
}

t_cmd			**ft_parsing(char *str, t_sys *sys, int n)
{
	t_cmd		**cmds;
	char		**tab;
	char		*tmp;

	if (!str)
		return (NULL);
	tmp = ft_tild(ft_varenv(str, sys->env), sys->env);
	ft_tild_file(&str, '\a', '~');
	if ((tab = ft_strsplit((tmp == NULL) ? str : tmp, ";")) == NULL)
		return (NULL);
	free(tmp);
	if ((cmds = malloc(sizeof(t_cmd) * (ft_tablen(tab) + 1))) == NULL)
		return (NULL);
	while ((size_t)n <= ft_tablen(tab))
		cmds[n++] = NULL;
	n = -1;
	while (tab[++n])
		if ((cmds[n] = ft_parsecmd(ft_check_alias(tab[n], sys->alias), NULL,
									NULL)) == NULL)
		{
			ft_free_cmds(cmds);
			return (NULL);
		}
	ft_free_tab(tab);
	return (cmds);
}
*/

static char		*ft_parse_parenthesis(char *str, char c, char r)
{
	size_t		n;
	char		*tmp;
	int			open;

	n = 0;
	open = FALSE;
	while (str[n])
	{
		if (str[n] == '\"')
		{
			if ((tmp = ft_delchar(str, (n > 0 && str[n - 1] == '\\')
									? n - 1 : n)) == NULL)
				return (NULL);
			str = tmp;
			open = (open == TRUE) ? FALSE : TRUE;
		}
		if (open == TRUE && str[n] == c)
			str[n] = r;
		n = n + 1;
	}
	return (str);
}

static void		ft_parenthesis_undo(char ***tab)
{
	size_t		n;
	size_t		i;

	n = 0;
	while ((*tab) && (*tab)[n])
	{
		i = 0;
		while ((*tab)[n][i])
		{
			if ((*tab)[n][i] == '\a')
				(*tab)[n][i] = ' ';
			i = i + 1;
		}
		n = n + 1;
	}
}

static t_cmd	*ft_parsecmd(char *str, char *tmp, char **tab)
{
	t_cmd		*cmd;

	if ((tmp = ft_parse_parenthesis(ft_strdup(str), ' ', '\a')) == NULL)
		return (NULL);
	if ((tab = ft_strsplit(tmp, " \t\n")) == NULL || !tab[0])
		return (NULL);
	free(tmp);
	if ((cmd = malloc(sizeof(t_cmd))) == NULL)
	{
		ft_free_tab(tab);
		return (NULL);
	}
	cmd->name = NULL;
	cmd->argv = NULL;
	cmd->redir = -1;
	ft_parenthesis_undo(&tab);
	if ((cmd->name = ft_strdup(tab[0])) == NULL)
	{
		ft_free_tab(tab);
		free(cmd);
		return (NULL);
	}
	cmd->argv = ft_tabcpy(tab);
	ft_free_tab(tab);
	free(str);
	return (cmd);
}

static t_cmd	*ft_redir(char redir)
{
	t_cmd		*cmd;

	if ((cmd = malloc(sizeof(t_cmd))) == NULL)
		return (NULL);
	cmd->name = NULL;
	cmd->argv = NULL;
	cmd->redir = redir;
	return (cmd);
}

static int		ft_check_sep(t_cmd *tree, t_cmd *node)
{
	int			t;
	int			n;

	if (tree->redir >= PIPE && tree->redir <= CONCAT_L)
		t = 1;
	if (tree->redir == FALSE)
		t = 0;
	if (node->redir >= PIPE && node->redir <= CONCAT_L)
		n = 1;
	if (node->redir == FALSE)
		n = 0;
	return (t - n);
}

int				ft_cmp_node(void *tree, void *node)
{
	t_cmd		*tmp;

	tmp = ((t_cmd *)(((t_btree *)tree)->item));
	if (tmp->redir != -1)
		return (ft_check_sep(tmp, ((t_cmd *)(((t_btree *)node)->item))));
	return (0);
}

static char		ft_get_redir(char *str, size_t i)
{
	char		redir;

	redir = (str[i] == '|') ? PIPE : FALSE;
	redir = (redir == FALSE && str[i] == '>' && str[i + 1] != '>') ?
		REDIR_R : redir;
	redir = (redir == FALSE && str[i] == '>' && str[i + 1] == '>') ?
		CONCAT_R : redir;
	redir = (redir == FALSE && str[i] == '<' && str[i + 1] != '<') ?
		REDIR_L : redir;
	redir = (redir == FALSE && str[i] == '<' && str[i + 1] == '<') ?
		CONCAT_L : redir;
	return (redir);
}

static t_btree	*ft_create_node(char *str, size_t n, size_t i, char redir)
{
	t_btree		*node;
	char		c;

	node = btree_create_node(ft_redir(redir));
	c = str[i];
	str[i] = '\0';
//	if ((redir == REDIR_L || redir == CONCAT_L) && (redir != 0))
//		node->right = btree_create_node(ft_parsecmd(ft_strdup(str + n), NULL, NULL));
//	else
	node->left = btree_create_node(ft_parsecmd(ft_strdup(str + n), NULL, NULL));
	if (redir != 0)
	{
		n = (redir == CONCAT_L || redir == CONCAT_R) ? i + 2 : i + 1;
		str[i] = c;
		i = (ft_strlchr(str + n, "|<>") == -1) ? ft_strlen(str) :
			ft_strlchr(str + n, "|<>") + n;
		c = str[i];
		str[i] = '\0';
//		if (redir == REDIR_L || redir == CONCAT_L)
//			node->left = btree_create_node(ft_parsecmd(ft_strdup(str + n), NULL, NULL));
//		else
		node->right = btree_create_node(ft_parsecmd(ft_strdup(str + n), NULL, NULL));
		str[i] = c;
		while (n < i && str[n] && c != '<')
			str[n++] = ' ';
	}
	return (node);
}

static void		ft_parsing_multicmd(t_btree **cmds, char *str)
{
	size_t		n;
	size_t		i;
	char		redir;

	n = 0;
	while (str[n])
	{
		i = (ft_strlchr(str + n, "|<>") == -1) ? ft_strlen(str) :
			ft_strlchr(str + n, "|<>") + n;
		redir = ft_get_redir(str, i);
		btree_add_node(&(*cmds), ft_create_node(str, n, i, redir),
					&ft_cmp_node);
		n = i;
		while (str[n] == '|' || str[n] == '<' || str[n] == '>')
			n = n + 1;
	}
}

void			ft_display(void *node)
{
	t_cmd		*tmp;
	int			n;

	n = 0;
	tmp = (t_cmd *)(((t_btree *)(node))->item);
	ft_putchar(' ');
	if (tmp->redir != -1)
	{
		if (tmp->redir == 0)
			ft_putstr(" ; ");
		if (tmp->redir == 1)
			ft_putstr(" | ");
		if (tmp->redir == 2)
			ft_putstr(" > ");
		if (tmp->redir == 3)
			ft_putstr(" >> ");
		if (tmp->redir == 4)
			ft_putstr(" < ");
		if (tmp->redir == 5)
			ft_putstr(" << ");
	}
	else
		while (tmp->argv[n])
			ft_putstr(tmp->argv[n++]);
}

t_btree			*ft_parsing(char *str, t_sys *sys)
{
	t_btree		*cmds;
	char		**tab;
	char		*tmp;
	int			n;

	if (!str)
		return (NULL);
	cmds = NULL;
	tmp = ft_tild(ft_varenv(str, sys->env), sys->env);
	ft_tild_file(&str, '\a', '~');
	if ((tab = ft_strsplit((tmp == NULL) ? str : tmp, ";")) == NULL)
		return (NULL);
	free(tmp);
	n = 0;
	while (tab[n])
		ft_parsing_multicmd(&cmds, tab[n++]);
	ft_free_tab(tab);
	return (cmds);
}
