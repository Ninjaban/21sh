/*
** create.c for  in /home/jonathan/rendu/termcaps
** 
** Made by Jonathan Carra
** Login   <jonathan@epitech.net>
** 
** Started on  Mon Oct 26 11:23:41 2015 Jonathan Carra
** Last update Tue Oct 27 09:45:25 2015 Jonathan Carra
*/

#include "include/my.h"

int	create_base(char *name)
{
  char	*str;
  char	*file;

  if ((str = malloc(4096)) == NULL)
    return (-1);
  read(0, str, 4096);
  file = combine2("touch ", combine(name, str, 0, 0), 1, 0);
  free(str);
  system(file);
  free(file);
  return (0);
}

int	create(char *name)
{
  struct termios        term;

  if (tcgetattr(0, &term) == -1)
    return (-1);

  cursergoto("ve", 1, 1);
  term.c_lflag = (ICANON);
  term.c_lflag &= (ECHO);
  if (tcsetattr(0, TCSADRAIN, &term) == -1)
    return (-1);

  my_putstr("Création d'un nouveau fichier :\n=>");
  if (create_base(name) == -1)
    return (-1);

  cursergoto("vi", 1, 1);
  term.c_lflag &= ~(ICANON);
  term.c_lflag &= ~(ECHO);
  if (tcsetattr(0, TCSADRAIN, &term) == -1)
    return (-1);
  return (0);
}
