/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:44:38 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/27 12:19:25 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

/*
**	<-- Define -->
*/

# define NAME "21sh"
# define PROMPT "\e[34;1;4m$: commande nº!#\e[0m - (\e[31m!W\e[0m)\n"
# define HISTORY_SIZE 1000
# define FALSE 0
# define TRUE 1
# define EXIT "exit"

# define PIPE 1
# define REDIR_R 2
# define CONCAT_R 3
# define REDIR_L 4
# define CONCAT_L 5

# define PIPE_OUT 0
# define PIPE_IN 1

# define LEFT 0
# define RIGHT 1

/*
**	<-- Includes -->
*/

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <dirent.h>
# include "libft.h"

/*
**	<-- Structures -->
*/

typedef struct	s_cmd
{
	char			*name;
	char			**argv;
}				t_cmd;

typedef struct	s_node
{
	char			node;
	t_cmd			*cmd;
	char			redir;
	int				fd;
}				t_node;

typedef struct	s_alias
{
	char			*key;
	char			*value;
	struct s_alias	*next;
}				t_alias;

typedef struct	s_sys
{
	struct termios	term_new;
	struct termios	term_save;
	t_alias			*alias;
	t_btree			*cmds;
	t_lst			*history;
	char			**env;
}				t_sys;

/*
**	<-- Functions -->
*/

/*
**	Parsing
*/

void			ft_parenthesis_undo(char ***tab);
void			ft_parse_parenthesis(char **str, char c, char r);
void			ft_init_node(t_btree **cmds, char *str, int fd);
void			ft_tild_file(char **str, char c, char r);
int				ft_check_alias(char **str, t_alias *alias, int n);
int				ft_true_node(void *root, void *item);
int				ft_false_node(void *root, void *item);
int				ft_get_redir_fd(char *str, size_t i);
char			*ft_varenv(char *str, char **env, char change);
char			*ft_tild(char *str, char **env);
t_cmd			*ft_parsecmd(char *str);
t_node			*ft_new_node(char node, char *str, char redir, int fd);
t_btree			*ft_parsing_line(char *str, t_sys *sys);
t_btree			*ft_parsing(char *str, t_sys *sys);

/*
**	Gestion d'erreur
*/

void			*ft_gestion_error(char *str);

/*
**	Tools
*/

int				ft_set_pwd(char ***env, char *str);
char			ft_delchar(char **str, size_t n);
char			*ft_strcut(char *str, size_t s, size_t e);
char			*ft_getenv(char **env, char *name);
char			*ft_path_join(char *src, char *str);
char			**ft_getpath(char **env);
size_t			ft_fpath(char **env, char *str);

/*
**	Exec
*/

void			ft_exec_child(t_node *node, t_sys **sys);
void			ft_exec_file(t_node *node, char redir);
void			ft_exec_read_file(t_node *node);
void			ft_exec_read_boucle(t_node *node);
void			*ft_exec_node(t_btree *root, t_sys **sys);
void			*ft_exec(t_sys **sys, t_btree *node, char *tmp, pid_t child);
int				ft_exec_open_file(char *str, char redir);
int				ft_access_dir(char *path);
char			*ft_access(char *name, char **env);

/*
**	Builtins
*/

void			ft_echo(char **argv);
void			ft_env(char **env);
void			ft_unsetenv(char ***env, char *str);
void			ft_setenv(char *str, char ***env, int b);
int				ft_alias(t_cmd *cmd, t_alias **alias);
int				ft_unalias(t_cmd *cmd, t_alias **alias);
int				ft_chdir(char ***env, char *str);
int				ft_builtins(t_cmd *cmds, t_sys **sys);

/*
**	Auto-completion
*/

void			ft_completion(char **str, size_t pos, char **env,
							char dassault);
void			ft_removecompl(char **str);
void			ft_opendir(t_btree **list, char *path);
void			ft_setcompletion(char **str, size_t pos, char *try, char tabul);
void			ft_completion_norme(char *word, t_btree **pattern,
									t_btree **list, char **env);
char			ft_checkcompl(char *str);
char			*ft_getword(char *str, size_t pos);
char			*ft_color(char *color, char *str);
char			*ft_getcdir(char *str);
char			*ft_getpattern(char *str);
char			*ft_getprob(t_btree *list, char *str);
int				match(char *s1, char *s2);
int				ft_cmpf(void *tree, void *item);
t_btree			*ft_getexec(char **path);

/*
**	History
*/

int				ft_history_init(t_lst **history, char **env);

/*
**	Free
*/

void			ft_delete_node(void *node);
void			ft_free_tab(char **tab);
void			ft_free(t_cmd **cmds, char **str, t_btree **cmd);
void			ft_sys_free(t_sys *sys);

/*
**	Prompt
*/

void			ft_prompt_path(char **t, char b);
void			ft_affprompt(size_t nbcmd, char **env);

/*
**	Read
*/

void			ft_print(char *str, size_t pos, char inc);
void			ft_read_print(char **str, int c, size_t *pos, char **env);
void			ft_read_suppr(char **str, size_t *pos);
void			ft_read_delete(char **str, size_t *pos);
void			ft_read_keyole(char **str, size_t *pos);
void			ft_read_keyori(char **str, size_t *pos);
void			ft_read_move(char **str, int c, size_t *pos);
int				ft_read(char **str, t_sys **sys);

/*
**	Main
*/

void			ft_check_parenthesis(t_sys **sys, char **str, char *tmp,
									size_t n);
void			ft_shell(t_sys *sys, int exit);
int				ft_history_maj(t_lst **history, char *line, char **env);
int				ft_sys_init(t_sys **sys);

#endif
