/*
** my_aff.c for  in /home/jonathan/rendu/termcaps
** 
** Made by Jonathan Carra
** Login   <jonathan@epitech.net>
** 
** Started on  Mon Oct 26 11:12:07 2015 Jonathan Carra
** Last update Tue Nov  3 13:36:08 2015 Jonathan Carra
*/

#include "include/my.h"

t_sh	aff_log(t_sh save)
{
  int	col;

  col = recup_line();
  my_putchar('\n');
  while (col > 1)
    {
      my_putchar('_');
      col = col - 1;
    }
  my_putchar('\n');
  if (save.log != NULL)
    {
      my_putstr(save.log);
      save.free_log = 1;
      save = free_all(NULL, NULL, save);
    }
  my_putchar('\n');
  return (save);
}

t_sh	aff_all(char **tab, int *select, t_sh save)
{
  char	*str;
  int	i;
  int	j;
  int	x;
  int	y;

  i = 0;
  y = 0;
  x = 0;
  j = 0;
  cursergoto("clear", 1, 1);
  while (i < save.doc)
    {
      cursergoto("cm", x, y);
      if (select[i] == 1)
	my_putstr("\033[7m");
      if (select[i] == 4)
	my_putstr("\033[33m");
      if (select[i] == 5)
	my_putstr("\033[31m");
      str = combine(save.name, tab[i], 0, 0);
      if (open_try(str) != -1)
	my_putstr("\033[34;1m");
      free(str);
      if (i == save.pos)
	{
	  cursergoto("us", 1, 1);
	  my_putstr(tab[i++]);
	  cursergoto("ue", 1, 1);
	}
      else
	my_putstr(tab[i++]);
      my_putstr("\033[0m");
      if (i < save.doc)
	{
	  x = x + save.sep;
	  j = j + 1;
	  if (j >= save.nbr)
	    {
	      x = 0;
	      y = y + 1;
	      j = 0;
	    }
	}
    }
  aff_log(save);
  return (save);
}

t_sh	set_log(char *str, t_sh save, int frees)
{
  int	n = 0;

  while (str[n] != '\0')
    n = n + 1;
  if ((save.log = malloc(sizeof(char) * (n + 1))) == NULL)
    return (save);
  n = 0;
  while (str[n] != '\0')
    {
      save.log[n] = str[n];
      n = n + 1;
    }
  save.log = '\0';
  if (frees == 1)
    free(str);
  return (save);
}
