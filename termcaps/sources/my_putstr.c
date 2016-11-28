/*
** my_putstr.c for  in /home/carra_j/Archive/base
** 
** Made by carra Jonathan
** Login   <carra_j@epitech.net>
** 
** Started on  Fri Jan 16 16:58:52 2015 carra Jonathan
** Last update Sat Jun 20 08:51:33 2015 carra Jonathan
*/

#include "include/my.h"

void	my_putstr(char *str)
{
  write(1, str, my_strlen(str));
}
