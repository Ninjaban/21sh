/*
** totab.c for  in /home/jonathan/rendu/termcaps
** 
** Made by Jonathan Carra
** Login   <jonathan@epitech.net>
** 
** Started on  Thu Oct 22 09:48:56 2015 Jonathan Carra
** Last update Tue Nov  3 13:46:30 2015 Jonathan Carra
*/

#include <stdlib.h>
#include "include/my.h"

char	**toTab(char *str)
{
  static char	**tab;
  int	i = 0;
  int	j = 0;
  int	n = 0;
  int	x;

  while (str[i] != '\0')
    {
      if (str[i] == '\n')
	j = j + 1;
      i = i + 1;
    }
  if ((tab = malloc(sizeof(char *) * j + 2)) == NULL)
    return (NULL);
  i = 0;
  j = 0;
  while (str[i - 1] != '\0' || i == 0)
    {
      if (str[i] == '\n')
        {
	  if ((tab[n] = malloc(sizeof(char *) * (i - j + 1))) == NULL)
            return (NULL);
	  x = 0;
	  while (j != i)
	    tab[n][x++] = str[j++];
	  tab[n][x] = '\0';
	  j = j + 1;
	  n = n + 1;
        }
      i = i + 1;
    }
  tab[n] = NULL;
  return (tab);
}
