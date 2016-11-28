/*
** actstr.c for  in /home/carra_j/rendu/PSU_2014_my_select
** 
** Made by carra Jonathan
** Login   <carra_j@epitech.net>
** 
** Started on  Mon Dec 29 10:21:19 2014 carra Jonathan
** Last update Sat Jun 20 08:46:34 2015 carra Jonathan
*/

#include "include/my.h"

char	*my_read(char *name)
{
  char	*str;
  int	fd;
  int	ret;

  if ((str = malloc(sizeof(char *) * 4096)) == NULL)
    return (NULL);
  if ((fd = open(name, O_RDONLY | O_CREAT, S_IRWXU)) == -1)
    return (NULL);
  if ((ret = read(fd, str, 4096)) == -1)
    return (NULL);
  close(fd);
  return (str);
}
