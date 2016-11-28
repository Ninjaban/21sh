/*
** my_free.c for  in /home/jonathan/rendu/termcaps
** 
** Made by Jonathan Carra
** Login   <jonathan@epitech.net>
** 
** Started on  Tue Oct 27 10:06:00 2015 Jonathan Carra
** Last update Tue Nov  3 13:47:19 2015 Jonathan Carra
*/

#include "include/my.h"

t_sh    free_structsave(t_sh save)
{
  int	n = 0;

  if (save.free_log == 1)
    {
      free(save.log);
      save.log = NULL;
      save.free_log = 0;
    }
  if (save.free_name == 1)
    {
      free(save.name);
      save.name = NULL;
      save.free_name = 0;
    }
  if (save.free_action == 1)
    {
      free(save.action);
      save.action = NULL;
      save.free_action = 0;
    }
  if (save.free_save == 1)
    {
      while (save.save[n] != NULL)
        free(save.save[n]);
      free(save.save);
      save.free_save = 0;
      save.save = NULL;
    }
  return (save);
}

t_sh	free_all(char **tab, int *select, t_sh save)
{
  int	n = 0;

  if (select != NULL)
    free(select);
  if (tab != NULL)
    {
      while (tab[n] != NULL)
	free(tab[n++]);
      free(tab);
    }
  free_structsave(save);
  return (save);
}
