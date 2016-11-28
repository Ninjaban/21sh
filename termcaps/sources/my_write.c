/*
** write_file.c for  in /home/carra_j/Archive/base
** 
** Made by carra Jonathan
** Login   <carra_j@epitech.net>
** 
** Started on  Fri Jan 16 17:02:41 2015 carra Jonathan
** Last update Sat Jun 20 08:52:30 2015 carra Jonathan
*/

#include "include/my.h"

int	my_write(char *str, char *name)
{
  int	fd;

  if ((fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
    return (1);
  write(fd, str, my_strlen(str));
  close (fd);
  return (0);
}
