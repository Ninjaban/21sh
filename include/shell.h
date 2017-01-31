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
**	Macros
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
**	Includes
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
**	Structures
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
**	Functions
*/

void			ft_free_tab(char **t);
void			ft_free_cmds(t_cmd **cmds);
void			ft_shell(t_sys *sys, int exit);
void			ft_affprompt(size_t nbcmd, char **env);
void			ft_prompt_path(char **t, char b);
void			ft_init_changedir(char **pwd, char **t, char ***env);
void			ft_alias_remove(t_alias **alias);
void			ft_tild_file(char **str, char c, char r);
void			ft_sys_free(t_sys *sys);
void			ft_parse_parenthesis(char **str, char c, char r);
void			*ft_gestion_error(char *str);
char			ft_delchar(char **str, size_t n);
int				ft_sys_init(t_sys **sys);
int				ft_access_dir(char *path);
int				ft_changedir(char *name, char *pwd, char *dir, char ***env);
int				ft_history_maj(t_lst **history, char *line, char **env);
int				ft_alias(t_cmd *cmd, t_alias **alias);
int				ft_unalias(t_cmd *cmd, t_alias **alias);
int				ft_set_pwd(char ***env, char *str);
int				ft_history_init(t_lst **history, char **env);
int				ft_read(char **str, t_sys **sys);
char			*ft_access(char *name, char **env);
char			*ft_joinpath(char *src, char *str);
char			*ft_strcut(char *str, size_t s, size_t e);
int				ft_check_alias(char **str, t_alias *alias, int n);
char			*ft_getenv(char **env, char *name);
char			*ft_path_join(char *src, char *str);
char			*ft_tild(char *str, char **env);
char			*ft_varenv(char *str, char **env);
char			**ft_getpath(char **env);
/*t_cmd			**ft_parsing(char *str, t_sys *sys, int n);*/
size_t			ft_fpath(char **env, char *str);

/*
**	Parsing
*/

int				ft_true_node(void *root, void *item);
int				ft_false_node(void *root, void *item);
t_cmd			*ft_parsecmd(char *str);
t_btree			*ft_parsing_line(char *str, t_sys *sys);
t_btree			*ft_parsing(char *str, t_sys *sys);

/*
**	Exec
*/

void			*ft_exec_node(t_btree *root, t_sys **sys);
void			*ft_exec(t_sys **sys);

/*
**	Builtins
*/

void			ft_echo(char **argv);
void			ft_env(char **env);
void			ft_unsetenv(char ***env, char *str);
void			ft_setenv(char *str, char ***env, int b);
int				ft_chdir(char ***env, char *str);

/*
**	Auto-completion
*/

void			ft_completion(char **str, size_t pos, char **env, char dassault);
void			ft_removecompl(char **str);
char			ft_checkcompl(char *str);
int				match(char *s1, char *s2);

/*
**	Free
*/

void			ft_delete_node(void *node);

void			ft_display(void *node);

#endif
