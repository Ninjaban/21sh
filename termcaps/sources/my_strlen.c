/*
** my_strlen.c for  in /home/carra_j/Archive/base
** 
** Made by carra Jonathan
** Login   <carra_j@epitech.net>
** 
** Started on  Fri Jan 16 18:10:24 2015 carra Jonathan
** Last update Sun Jan 18 13:22:35 2015 carra Jonathan
*/

#include "include/my.h"

int     my_strlen(char *str)
{
  int   n;

  n = 0;
  while (str[n] != '\0')
    n = n + 1;
  return (n);
}
