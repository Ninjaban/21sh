/*
** recup-ligne.c for  in /home/jonathan/rendu/termcaps
** 
** Made by Jonathan Carra
** Login   <jonathan@epitech.net>
** 
** Started on  Thu Oct 22 17:03:21 2015 Jonathan Carra
** Last update Mon Oct 26 13:03:02 2015 Jonathan Carra
*/

#include <sys/ioctl.h>
#include <stdio.h>
#include "include/my.h"

int	recup_line()
{
  struct winsize w;
  int	nbr = 0;

  ioctl(0, TIOCGWINSZ, &w);
  nbr = w.ws_col;
  return nbr;
}

int	init_separator(char **tab, int lenght)
{
  int	n = 0;
  int	i = 0;
  int	j;
  int	col;

  col = recup_line();
  while (i < lenght)
    {
      j = 0;
      while (tab[i][j] != '\0')
	j = j + 1;
      if (j > n)
	n = j;
      i = i + 1;
    }
  n = n + 1;
  if (n  > col)
    {
      my_putstr("Votre terminal est trop petit!");
      return (-1);
    }
  else
    return (n);
}

int	nbr_sep(int sep)
{
  int	col;
  int	n = 0;

  col = recup_line();
  my_putnbr(col);
  while ((col = col - sep) > -1)
    n = n + 1;
  my_putnbr(n);
  return (n);
}
