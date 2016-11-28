/*
** my_select.c for  in /home/jonathan/rendu/termcaps
** 
** Made by Jonathan Carra
** Login   <jonathan@epitech.net>
** 
** Started on  Thu Oct 22 11:40:11 2015 Jonathan Carra
** Last update Tue Nov  3 14:01:49 2015 Jonathan Carra
*/

#include "include/my.h"

int	open_try(char *name)
{
  DIR	*dir;

  if ((dir = opendir(name)) == NULL)
    return (-1);
  free(dir);
  return (0);
}

char    *combine(char *str1, char *str2, int f1, int f2)
{
  char  *result;
  int   i = 0;
  int   j = 0;

  while (str1[i] != '\0')
    i = i + 1;
  while (str2[j] != '\0')
    j = j + 1;
  if ((result = malloc(sizeof(char) * (i + j + 2))) == NULL)
    return (NULL);
  i = 0;
  j = 0;
  while (str1[i] != '\0')
    result[j++] = str1[i++];
  result[j++] = '/';
  i = 0;
  while (str2[i] != '\0')
    result[j++] = str2[i++];
  result[j] = '\0';
  if (f1 == 1)
    free(str1);
  if (f2 == 1)
    free(str2);
  return (result);
}

char	*combine2(char *str1, char *str2, int f1, int f2)
{
  char	*result;
  int	i = 0;
  int	j = 0;

  while (str1[i] != '\0')
    i = i + 1;
  while (str2[j] != '\0')
    j = j + 1;
  if ((result = malloc(sizeof(char) * (i + j + 1))) == NULL)
    return (NULL);
  i = 0;
  j = 0;
  while (str1[i] != '\0')
    result[j++] = str1[i++];
  i = 0;
  while (str2[i] != '\0')
    result[j++] = str2[i++];
  result[j] = '\0';
  if (f1 == 1)
    free(str1);
  if (f2 == 1)
    free(str2);
  return (result);
}

int	my_select(char *str, t_sh save)
{
  char	**tab;
  int	*select;
  int	i = 0;
  int	reload = 0;

  save.doc = 0;
  save.pos = 0;
  save.nbr = 1;
  save.sep = 1;

  tab = toTab(str);

  while (str[i] != '\0')
    {
      if (str[i] == '\n')
        save.doc = save.doc + 1;
      i = i + 1;
    }
  if ((select = malloc(sizeof(int) * ( save.doc + 1 ))) == NULL)
    return (-1);
  i = 0;
  while (i < save.doc)
    select[i++] = 0;

  sort_cstrings(tab, save.doc);

  if ((save.sep = init_separator(tab, save.doc)) == -1)
    return (-1);
  save.nbr = nbr_sep(save.sep);
  while (save.pos >= 0)
    {
      save = aff_all(tab, select, save);
      if ((save.pos =
	   voir_touche(save.pos, save.doc, save.nbr, select)) == -1)
	return (-1);
      if (select[save.pos] == 2)
	{
	  str = combine(save.name, tab[save.pos], 0, 0);
	  if (open_try(str) != -1)
	    {
	      free(str);
	      str = combine2("Accès au dossier : ", tab[save.pos], 0, 0);
	      save = set_log(str, save, 1);
	      save.name = combine(save.name, tab[save.pos], 1, 0);
	      if ((str = my_ls(save.name)) == NULL)
		return (-1);
	      reload = 1;
	    }
	  else
	    {
	      free(str);
	      str = combine2("emacs -nw ", combine(save.name, tab[save.pos]
						   , 0, 0), 0, 1);
	      system(str);
	      free(str);
	    }
	}
      if (select[save.pos] == 3)
	{
	  select_rm(tab, select, save.name, save.doc);
	  if ((str = my_ls(save.name)) == NULL)
	    return (-1);
	  reload = 1;
	}
      if (select[save.pos] == 4 || select[save.pos] == 5)
	{
          save = save_location(tab, select, save.name, save);
          if ((str = my_ls(save.name)) == NULL)
            return (-1);
          reload = 1;
	}
      if (select[save.pos] == 6)
	{
	  if (save.action != NULL)
	    {
	      select_coller(save.save, save.action, save.name);
	      if ((str = my_ls(save.name)) == NULL)
		return (-1);
	      reload = 1;
	    }
	}
      if (save.pos == -3)
	{
	  create(save.name);
	  reload = 1;
	}
      if (reload == 1)
	{
	  free_all(tab, select, save);
          if (my_select(str, save) == -1)
            return (-1);
	}
    }
  select_cd(save.name);
  free_all(tab, select, save);
  end(save);
  return (0);
}
