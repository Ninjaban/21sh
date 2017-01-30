/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/11 08:42:36 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

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

static void		ft_parse_backslash(char *str)
{
	size_t		n;

	n = 0;
	if ((str)[n + 1] == 'n')
		(str)[n] = '\n';
	else
		return;
	n = n + 1;
	while ((str)[n++])
		(str)[n - 1] = (str)[n];
}

static void		ft_parse_parenthesis_open(char *str, char c, char r, char type)
{
	size_t		n;

	n = 0;
	while (str[n] && str[n] != ((type == 0) ? '\"' : '\''))
	{
		if (str[n] == c)
			str[n] = r;
		if (type == 1 && str[n] == '\\' && c != r)
			ft_parse_backslash(str + n);
		n = n + 1;
	}
	while ((str)[n++])
		(str)[n - 1] = (str)[n];
}

void			ft_parse_parenthesis(char **str, char c, char r)
{
	size_t		n;

	n = 0;
	while ((*str)[n])
	{
		if ((*str)[n] == '\"' || (*str)[n] == '\'')
		{
			ft_parse_parenthesis_open((*str) + n + 1, c, r,
									  ((*str)[n] == '\"') ? 0 : 1);
			if (((*str)[n] == '\"' || (*str)[n] == '\'') &&
				((ft_delchar(&(*str), n)) == FALSE))
				return ;
		}
		else
			n = n + 1;
	}
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

t_cmd			*ft_parsecmd(char *str)
{
	t_cmd		*cmd;
	char		**tab;

	ft_parse_parenthesis(&str, ' ', '\a');
	if ((tab = ft_strsplit(str, " \t")) == NULL || !tab[0])
		return (NULL);
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

static t_node	*ft_new_node(char node, char *str, char redir, int fd)
{
	t_node		*new;

	if ((new = malloc(sizeof(t_node))) == NULL)
		return (NULL);
	new->node = node;
	new->cmd = (str) ? ft_parsecmd(ft_strdup(str)) : NULL;
	new->redir = redir;
	new->fd = fd;
	return (new);
}

/*
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
*/

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

static int		ft_get_redir_fd(char *str, size_t i)
{
	size_t		n;

	n = 1;
	if (i == 0 || str[i] != '>')
		return (1);
	if (ft_isdigit(str[i - 1]) == FALSE)
		return (1);
	while (i - n > 0 && ft_isdigit(str[i - n]))
		n = n + 1;
	return (ft_atoi(str + ((i - n == 0) ? i - n : i - n + 1)));
}
/*
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
*/
void			ft_display(void *node)
{
	t_node		*root;
	t_cmd		*cmd;
	int			n;

	n = 0;
	root = (t_node *)((t_btree *)node)->item;
	cmd = (t_cmd *)(root->cmd);
	if (root->node == FALSE)
		ft_putstr(" ; ");
	else if (root->redir != FALSE)
	{
		ft_putnbr(root->fd);
		if (root->redir == 1)
			ft_putstr(" | ");
		else if (root->redir == 2)
			ft_putstr(" > ");
		else if (root->redir == 3)
			ft_putstr(" >> ");
		else if (root->redir == 4)
			ft_putstr(" < ");
		else if (root->redir == 5)
			ft_putstr(" << ");
		else
			ft_putnbr(root->redir);
	}
	else
		while (cmd->argv[n])
			ft_putstr(cmd->argv[n++]);
}

static void		ft_init_node(t_btree **cmds, char *str, int fd)
{
	size_t		n;
	char		redir;

	n = 0;
	if ((redir = ft_get_redir(str, n)) != FALSE)
	{
		btree_add_node(&(*cmds), btree_create_node(
						   ft_new_node(TRUE, NULL, redir, fd)), &ft_true_node);
		while (str[n] == '|' || str[n] == '<' || str[n] == '>')
			n = n + 1;
	}
	btree_add_node(&(*cmds), btree_create_node(
					   ft_new_node(TRUE, str + n, FALSE, FALSE)), &ft_true_node);
}

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

int				ft_true_node(void *root, void *item)
{
	if (((t_btree *)root)->right &&
		((t_node *)(((t_btree *)root)->item))->node == FALSE)
		return (0);
	if (((t_btree *)root)->left)
		return (-1);
	if (((t_node *)(((t_btree *)item)->item))->redir != FALSE)
		return (-1);
	if (!((t_btree *)root)->right)
		return ((((t_node *)(((t_btree *)root)->item))->node != FALSE)
				? 0 : -1);
	return (-1);
}

int				ft_false_node(void *root, void *item)
{
	(void)root;
	(void)item;
	return (0);
}

static void		ft_add_node(t_btree **cmds, char **tab, int n)
{
	if (tab[n])
	{
		if (n > 0)
			btree_add_node(&(*cmds), btree_create_node(
					ft_new_node(FALSE, NULL, FALSE, FALSE)), &ft_false_node);
		ft_tild_file(&(tab[n]), '\a', ';');
		ft_parsing_multicmd(&(*cmds), tab[n]);
		ft_add_node(&(*cmds), tab, n + 1);
	}
}

t_btree			*ft_parsing_line(char *str, t_sys *sys)
{
	t_btree		*cmds;
	char		**tab;
	char		*tmp;

	tmp = ft_tild(ft_varenv(str, sys->env), sys->env);
	ft_tild_file(&tmp, ';', '\a');
	if ((tab = ft_strsplit(tmp, ";")) == NULL)
	{
		free(str);
		free(tmp);
		return (NULL);
	}
	free(str);
	free(tmp);
	cmds = btree_create_node(ft_new_node(FALSE, NULL, FALSE, FALSE));
	ft_add_node(&cmds, tab, 0);
/*	while (tab[n])
	{
		if (n > 0)
			btree_add_node(&cmds, btree_create_node(
					ft_new_node(FALSE, NULL, FALSE, FALSE)), &ft_false_node);
		ft_parsing_multicmd(&cmds, tab[n++]);
	}*/
	ft_free_tab(tab);
	btree_apply_infix(cmds, &ft_display);
	ft_putendl("");
	return (cmds);
}

t_btree			*ft_parsing(char *str, t_sys *sys)
{
	t_btree		*cmds;
//	char		*new;

	if (!str)
		return (NULL);
	cmds = ft_parsing_line(str, sys);
	return (cmds);
}