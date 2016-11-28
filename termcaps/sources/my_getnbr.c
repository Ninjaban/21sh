/*
** my_getnbr.c for  in /home/carra_j/Archive/base
** 
** Made by carra Jonathan
** Login   <carra_j@epitech.net>
** 
** Started on  Fri Jan 16 17:00:15 2015 carra Jonathan
** Last update Sun Jan 18 13:19:56 2015 carra Jonathan
*/

#include "include/my.h"

int	my_getnbr(char *str)
{
  int	n;
  int	i;
  int	neg;

  n = 0;
  i = 0;
  neg = 0;
  while (str[n] != '\0')
    {
      if (str[n] >= 48 && str[n] <= 57)
        {
          i = i * 10;
          if (str[n - 1] == 45)
            neg = 1;
          i = str[n] - 48 + i;
        }
      n = n + 1;
    }
  if (neg == 1)
    i = i * -1;
  return (i);
}
