/*
** my.h for  in /home/carra_j/rendu/CPE_2014_bsq
** 
** Made by carra Jonathan
** Login   <carra_j@epitech.net>
** 
** Started on  Mon Jan  5 10:06:48 2015 carra Jonathan
** Last update Fri Jan 22 14:25:23 2016 Jonathan Carra
*/

#ifndef MY_H_
# define MY_H_

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <dirent.h>

typedef struct  s_sh
{
  char          *log;
  int		free_log;
  char		*name;
  int		free_name;
  char		**save;
  int		free_save;
  int		*action;
  int		free_action;
  int		doc;
  int		pos;
  int		sep;
  int		nbr;
}               t_sh;


void	my_putchar(char c);
void	my_putstr(char *str);
void	my_putnbr(int nbr);
void    sort_cstrings(char *strings[], int len);
void    print_cstring_array(char **array, size_t len);
void	freetab(char **, int);
void    select_rm(char **, int *, char *, int);
void	end();
void    select_coller(char **save, int *select, char *cible);
void    select_copier(int *select, int pos, int lenght);
void    select_couper(int *select, int pos, int lenght);
void	select_cd(char *name);
int	my_write(char *str, char *name);
int	my_revnbr(int n);
int	my_strlen(char *str);
int	my_getnbr(char *str);
int	my_select(char *str, t_sh save);
int	cursergoto(char *cmd, int colone, int line);
int     voir_touche(int pos, int lenght, int nbr_sep, int *select);
int	nbr_sep(int sep);
int     recup_line();
int     open_try(char *name);
int     init_separator(char **, int);
int     create(char *name);
char	*my_read(char *name);
char	*my_ls(char *name);
char	*combine(char *, char *, int , int);
char	*combine2(char *, char *, int, int);
char	**toTab(char *str);
t_sh    save_location(char **, int *, char *, t_sh);
t_sh    set_log(char *str, t_sh save, int frees);
t_sh    aff_all(char **, int *, t_sh save);
t_sh    free_all(char **, int *, t_sh save);

#endif /* !MY_H_ */
