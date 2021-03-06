/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:44:38 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/18 17:54:26 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FICHIER :: SHELL HEADER
**   Fichier contenant toutes les structures, defines et prototypes qui
**   concernent le shell directement.
*/

#ifndef SHELL_H
# define SHELL_H

/*
** DEFINES :: Motif général
**   NAME				Nom du shell
**   PROMPT				Prompt de base, avec les couleurs
**   HISTORY_SIZE		Taille maximale de l'historique sauvegardé
**   TRUE - FALSE		mots clés classiques
**   EXIT				mot clé de sortie du terminal
*/

# define NAME			"21sh"
# define PROMPT			"\e[34;1;4m$: commande nº!#\e[0m - (\e[31m!W\e[0m)\n"
# define HISTORY_SIZE	25
# define FALSE			0
# define TRUE			1
# define EXIT			"exit"

/*
** DEFINES :: Mots clés de condition
**   CMD				point virgule ;
**   AND				double ET &&
**   OR					double OU ||
*/

# define CMD			3
# define AND			4
# define OR				5

/*
** DEFINES :: Mots clés de redirection
**	 PIPE				|  pipe
**	 REDIR_R				>  redirection droite simple
**	 CONCAT_R			>> redirection droite double
**	 REDIR_L				<  redirection gauche simple
**	 CONCAT_L			<< redirection gauche double
**	 PIPE_OUT			sortie d'un pipe
**	 PIPE_IN			entrée d'un pipe
*/

# define PIPE			1
# define REDIR_R		2
# define CONCAT_R		3
# define REDIR_L		4
# define CONCAT_L		5

# define PIPE_OUT		0
# define PIPE_IN		1
# define STD_ALL		-1

/*
** DEFINES :: ?
**	LEFT				quelque chose à gauche ?
**	RIGHT				quelque chose à droite ?
*/

# define LEFT 			0
# define RIGHT 			1

/*
** DEFINES :: checks
**   IS_REDIR_CHAR      si c'est un caractère de redirection (><&|)
**   IS_BLANK           si c'est un caractère blanc (' ', '\t')
**   IS_INHIB           si c'est un caractère inhibiteur (quotes)
**   IS_CHEV            (voir IS_CCA)
**   IS_CCA		        si c'est une suite égale à &>>
*/

# define IS_REDIR_CHAR(x)	(x == '&' || x == '<' || x == '>' || x == '|')
# define IS_BLANK(x)		(x ==' ' || x == '\n')
# define IS_INHIB(x)		(x =='\'' || x == '"')
# define IS_CHEV(x,y)		(x[y - 1] == '>')
# define IS_CCA(x,y)		(IS_CHEV(x,y) && x[y - 2] == '>' && x[y - 3] == '&')
# define IS_AC(x,y)			(x[y - 1] == '&' && x[y] == '>')
# define IS_CA(x,y)			(x[y - 1] == '>' && x[y] == '&')
# define IS_ACCA(x,y)		(IS_AC(x,y) || IS_CA(x,y))

/*
** INCLUDES
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
# include <sys/types.h>
# include <pwd.h>
# include "libft.h"

/*
** STRUCTURE :: CoMmanDe
**   Structure de gestion des commandes
**
** VARIABLES
**   char*			name		path complet de la commande
**   char**			argv		arguments de la commande
*/

typedef struct	s_cmd
{
	char			*name;
	char			**argv;
}				t_cmd;

/*
** STRUCTURE :: NODE
**   Structure de gestion des noeuds de l'arbre binaire
**
** VARIABLES
**   char			node		CMD, AND, ou OR. FALSE si ce n'est pas une
** 																	  condition.
**   t_cmd*			cmd			structure de la commande en cours, NULL si ce
**														  n'est pas une commande
**	 char			redir		un des defines de redirection. FALSE sinon
** 	 int			fd			file descriptor
*/

typedef struct	s_node
{
	char			node;
	t_cmd			*cmd;
	char			redir;
	int				fd;
}				t_node;

/*
** STRUCTURE :: ALIAS
**   Liste chaînée des alias
**
** VARIABLES
**   char*			key			clé de l'alias
**   char*			value		valeur de l'alias
**   t_alias*		next		alias suivant dans la structure
*/

typedef struct	s_alias
{
	char			*key;
	char			*value;
	struct s_alias	*next;
}				t_alias;

/*
** STRUCTURE :: HISTorique
**   Liste chaînée des valeurs enregistrées dans l'historique
**
** VARIABLES
**   char*			line		ligne de commande
**   int			id			id de la ligne de commande
*/

typedef struct	s_hist
{
	char			*line;
	int				id;
}				t_hist;

/*
** STRUCTURE :: SYStem
**   structure système, contenant tout ce dont le programme a besoin quasiment
**   en permanence.
**
** VARIABLES
**   struct termios	term_new	term_new
**   struct termios	term_save	term_save
**   t_alias*		alias		liste des alias définis
**   t_btree*		cmds		arbre binaire des commandes
**   t_lst*			history		historique
**   int*			keymap		tableau d'ints contenant les touches actives
**   char**			env			variable d'environnement
**   char**			shvar		variables locales (set)
**   char**			ftvar		variables locales fonctionnelles (ajouter une
** 										 fonction est impossible pour le moment)
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
** FUNCTIONS
*/

/*
**	Parsing
*/

void			ft_parenthesis_undo(char ***tab);
void			ft_parse_parenthesis(char **str);
void			ft_parse_parenthesis_open_init(char **src);
void			ft_init_node(t_btree **cmds, char *str, int fd);
void			ft_tild_file(char **str, char c, char r);
int				ft_check_alias(char **str, t_alias *alias, int n);
int				ft_true_node(void *root, void *item);
int				ft_false_node(void *root, void *item);
int				ft_parsing_count_word(char const *s);
int				ft_get_redir_fd(char *str, size_t i);
char			*ft_varenv(char *str, t_sys *sys, char change);
char			*ft_getpwd(char **env, char **shvar);
char			*ft_tild(char *str, char **env, char **shvar);
char			*ft_parsing_semicolon(char *str);
char			**ft_parsing_split(char const *s);
t_cmd			*ft_parsecmd(char *str);
t_node			*ft_new_node(char node, char *str, char redir, int fd);
t_btree			*ft_parsing_line(char *str, t_sys *sys);
t_btree			*ft_parsing(char *str, t_sys *sys);

/*
**	Gestion d'erreur
*/

void			*ft_gestion_error(char *str);
char			*ft_gestion_error_check_redir(char *str);
char			*ft_check_semicolon_syntax(char *cmd);
char			ft_check_syntax_three(char *cmd);
char			ft_check_syntax_start(char *cmd);
char			ft_check_syntax_before(char *cmd);
char			ft_check_syntax_twins(char *cmd);

/*
**	Tools
*/

int				ft_set_pwd(char ***env, char ***shvar, char *str);
int				ft_del_line(char ***env, size_t i);
char			ft_delchar(char **str, size_t n);
char			*ft_getenv(char **env, char**shvar, char *name);
char			*ft_path_join(char *src, char *str);
char			**ft_getpath(char **env);
size_t			ft_fpath(char **env, char *str);
size_t			ft_find_path(char **tab, char *str);

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
char			*ft_access(char *name, char **env, char **shvar);

/*
**	Builtins
*/

void			ft_path_trim(char **str);
char			ft_keymap(int **keymap, char **argv, t_sys *sys);
char			ft_help(char **av, char **env, char **shvar);
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
int				ft_chdir(char ***env, char ***shvar, char **argv);
int				ft_chdir_options(char **argv, char *opt);
int				ft_chdir_set_path(char **path, char *str);
int				ft_chdir_path_norme(int *res, char *path, char **tab,
									char ****env);
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

void			ft_completion(char **str, size_t pos, t_sys *sys,
							char dassault);
void			ft_removecompl(char **str);
void			ft_opendir(t_btree **list, char *path, char diropen);
void			ft_setcompletion(char **str, size_t pos, char *try, char tabul);
void			ft_completion_norme(char *word, t_btree **list,
									char **env, char **shvar);
char			ft_checkcompl(char *str);
char			ft_access_dir_cplt(char *path);
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

void			ft_list_push_back_id(t_lst **begin_list, char *line);
int				ft_history_init(t_lst **history, char **env, char **shvar);
t_lst			*ft_create_hist_elem(char *line);

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

void			ft_affprompt(size_t nbcmd, char **env, char **shvar);
char			*ft_path(char *str, char **env, char **shvar, size_t *n);

/*
**	Read
*/

void			ft_sigint(int sig);
void			ft_print(char *str, size_t pos, int inc, char resetstatic);
void			ft_print_norme(char **tmp, size_t pos, int inc);
void			ft_read_print(char **str, int c, size_t *pos, t_sys **sys);
void			ft_read_suppr(char **str, size_t *pos);
void			ft_read_delete(char **str, size_t *pos);
void			ft_read_keyole(char **str, size_t *pos);
void			ft_read_keyori(char **str, size_t *pos);
void			ft_read_move(char **str, int c, size_t *pos, t_sys *sys);
void			ft_read_cpy_past(char **str, size_t *n, char type, char new);
void			ft_read_history_do(char **str, t_sys **sys,
									size_t *i, size_t *pos);
void			ft_read_history_up(char **str, t_sys **sys,
									size_t *i, size_t *pos);
void			ft_read_keymap_init(t_sys **sys);
void			ft_putstr_limit(char *color, size_t pos, size_t limit);
char			ft_read_check(int c, char **str, t_sys **sys, size_t *n);
int				ft_read(char **str, t_sys **sys, size_t n, char exit);

/*
**	Coloration Syntaxique
*/

void			ft_read_color_main(char *str, size_t pos, size_t limit);
void			ft_strcopy_color(char **src, char *str, size_t *n);
char			ft_check_sep(char *str);
char			*ft_read_color_inhibitor(char *str);
char			*ft_read_color_sudo(char *str);
char			*ft_read_color_first(char *str);
char			*ft_read_color_hyphen(char *str);
char			*ft_read_color_fd(char *str);
char			*ft_read_color_redirect(char *str);

/*
**	Signaux
*/

char			ft_signal_start(void);
char			ft_signal_stop(void);

/*
**	Main
*/

void			ft_check_excl(t_sys **sys, char **str);
void			ft_check_inhibitor(t_sys **sys, char **str);
void			ft_shell(t_sys *sys, int exit, char *str, char *tmp);
int				ft_history_maj(t_lst **history, char *line,
								char **env, char **shvar);
int				ft_shrc_init(t_sys **sys, char *str, int fd);
int				ft_sys_init(t_sys **sys);

#endif
