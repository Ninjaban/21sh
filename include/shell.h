/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:44:38 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/21 10:53:01 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

/*
**	<-- Define -->
*/

# define NAME "21sh"
# define PROMPT "\e[34;1;4m$: commande nº!#\e[0m - (\e[31m!W\e[0m)\n"
# define HISTORY_SIZE 25
# define FALSE 0
# define TRUE 1
# define EXIT "exit"

/*
**	CMD	= ;
**	AND	= &&
**	OR	= ||
*/

# define CMD 3
# define AND 4
# define OR 5

# define CHAR_CMD -1
# define CHAR_AND -2
# define CHAR_OR -3

/*
**	PIPE		= |
**	REDIR_R		= >
**	CONCAT_R	= >>
**	REDIR_L		= <
**	CONCAT_L	= <<
*/

# define NOREDIR 0
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

typedef struct	s_hist
{
	char			*line;
	int				id;
}				t_hist;

/*
** env		-> environment variables
** shvar	-> local variables
** ftvar	-> local functions (cannot add functions yet)
*/

typedef struct	s_sys
{
	struct termios	term_new;
	struct termios	term_save;
	t_alias			*alias;
	t_btree			*cmds;
	t_lst			*history;
	int				*keymap;
	char			**env;
	char			**shvar;
	char			**ftvar;
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
char			*ft_varenv(char *str, t_sys *sys, char change);
char			*ft_tild(char *str, char **env);
t_cmd			*ft_parsecmd(char *str);
t_node			*ft_new_node(char node, char *str, char redir, int fd);
t_btree			*ft_parsing_line(char *str, t_sys *sys);
t_btree			*ft_parsing(char *str, t_sys *sys);

char			**ft_parsing_split(char const *s);
int				ft_parsing_count_word(char const *s);

/*
**	Gestion d'erreur
*/

void			*ft_gestion_error(char *str);

/*
**	Tools
*/

int				ft_set_pwd(char ***env, char *str);
int				ft_del_line(char ***env, size_t i);
char			ft_delchar(char **str, size_t n);
char			*ft_strcut(char *str, size_t s, size_t e);
char			*ft_getenv(char **env, char *name);
char			*ft_path_join(char *src, char *str);
char			**ft_getpath(char **env);
size_t			ft_fpath(char **env, char *str);
size_t			ft_find_path(char **tab, char *str);
void			ft_init_pwd(char ***env);

/*
**	Exec
*/

void			ft_exec_child(t_node *node, t_sys **sys);
void			ft_exec_file(t_node *node, char redir);
void			ft_exec_read_file(t_node *node);
void			ft_exec_read_boucle(t_node *node);
void			*ft_exec_node(t_btree *root, t_sys **sys);
void			*ft_exec(t_sys **sys, t_btree *node, char *tmp);
int				ft_exec_open_file(char *str, char redir);
int				ft_access_dir(char *path);
char			*ft_access(char *name, char **env);

/*
**	Builtins
*/

void			ft_path_trim(char **str);
char			ft_keymap(int **keymap, char **argv, t_sys *sys);
char			ft_help(char **av, char **env);
char			*ft_chdir_opt_p(char *path, char opt);
char			*ft_hist_str(char *str);
char			*ft_hist_id(t_lst *history, char *str);
char			*ft_hist_find(t_lst *history, char *str);
char			*ft_hist_last(t_lst *history);
char			**ft_getcdpath(char **env);
int				ft_echo(char **argv);
int				ft_env(char **argv, char **env, char ***shvar);
int				ft_unsetenv(char ***env, char *str);
int				ft_setenv(char *str, char ***env, char ***shvar, int b);
int				ft_alias(t_cmd *cmd, t_alias **alias);
int				ft_unalias(t_cmd *cmd, t_alias **alias);
int				ft_chdir(char ***env, char **argv);
int				ft_chdir_options(char **argv, char *opt);
int				ft_chdir_set_path(char **path, char *str);
int				ft_chdir_cdpath(char **path, char **cdpath, char **tab);
int				ft_set(char **cmd, char ***env, char ***shvar);
int				ft_unset(char ***env, char ***shvar, char ***ftvar, char **cmd);
int				ft_export(char **cmd, char ***env, char ***shvar);
int				ft_hist_built(char **argv, t_lst **history);
int				ft_builtins(t_cmd *cmds);
int				ft_exec_builtins(t_cmd *cmds, t_sys **sys);
int				ft_alias_init(t_cmd *cmd, t_alias **alias);
t_alias			*ft_alias_new(char *key, char *value);

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
t_lst			*ft_create_hist_elem(char *line);
void			ft_list_push_back_id(t_lst **begin_list, char *line);

/*
**	Free
*/

void			ft_delete_node(void *node);
void			ft_free_tab(char **tab);
void			ft_free(t_cmd **cmds, char **str, t_btree **cmd);
void			ft_sys_free(t_sys *sys);
void			ft_free_hist(void *data);

/*
**	Prompt
*/

void			ft_prompt_path(char **t, char b);
void			ft_affprompt(size_t nbcmd, char **env);

/*
**	Read
*/

void			ft_sigint(int sig);
void			ft_print(char *str, size_t pos, char inc);
void			ft_read_print(char **str, int c, size_t *pos, t_sys **sys);
void			ft_read_suppr(char **str, size_t *pos);
void			ft_read_delete(char **str, size_t *pos);
void			ft_read_keyole(char **str, size_t *pos);
void			ft_read_keyori(char **str, size_t *pos);
void			ft_read_move(char **str, int c, size_t *pos, t_sys *sys);
void			ft_read_history_clear(char *str);
void			ft_read_cpy_past(char **str, size_t *n, char type, char new);
int				ft_read(char **str, t_sys **sys, size_t n, char exit);

/*
**	Signaux
*/

char			ft_signal_start(void);
char			ft_signal_stop(void);

/*
**	Main
*/

void			ft_check_excl(t_sys **sys, char **str);
void			ft_check_parenthesis(t_sys **sys, char **str, char *tmp,
									size_t n);
void			ft_shell(t_sys *sys, int exit, char *str, char *tmp);
int				ft_history_maj(t_lst **history, char *line, char **env);
int				ft_shrc_init(t_sys **sys, char *str, int fd);
int				ft_sys_init(t_sys **sys);

#endif
