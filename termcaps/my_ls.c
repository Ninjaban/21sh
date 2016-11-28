/*
** my_ls.c for  in /home/jonathan/rendu/termcaps
** 
** Made by Jonathan Carra
** Login   <jonathan@epitech.net>
** 
** Started on  Wed Oct 21 17:02:43 2015 Jonathan Carra
** Last update Thu Oct 29 10:33:47 2015 Jonathan Carra
*/

#include "include/my.h"

int     savestr(char *str, char *str2, int n)
{
  int   i = 0;

  while (str[i] != '\0')
    {
      str2[n] = str[i];
      i = i + 1;
      n = n + 1;
    }
  str2[n] = '\n';
  str2[n + 1] = '\0';
  return (*str2);
}

int     charstr(char *str, int n)
{
  n = 0;
  while (str[n] != '\0')
    n = n + 1;
  return (n);
}

void     error(char *name)
{
  my_putstr("my_ls: cannot access ");
  my_putstr(name);
  my_putstr(": No such file or directory\n");
}

char     *my_ls(char *name)
{
  DIR   *direct;
  struct dirent *files;
  char  *str;
  int   n = 0;

  if ((str = malloc(sizeof(char) * 4096)) == NULL)
    return (NULL);
  if ((direct = opendir(name)) == NULL)
    return (NULL);
  while ((files = readdir(direct)) != '\0')
    {
      *str = savestr(files->d_name, str, n);
      n = charstr(str, n);
    }
  free(direct);
  return (str);
}
