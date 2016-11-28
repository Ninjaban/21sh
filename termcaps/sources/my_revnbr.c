/*
** my_revnbr.c for  in /home/carra_j/rendu/CPE_2014_bsq
** 
** Made by carra Jonathan
** Login   <carra_j@epitech.net>
** 
** Started on  Fri Jan 16 16:52:58 2015 carra Jonathan
** Last update Wed Jan 21 09:47:28 2015 carra Jonathan
*/

#include "include/my.h"

int	my_revnbr(int n)
{
  int	i;

  i = 1;
  while (n != 0)
    {
      i = i * 10;
      i = n % 10 + i;
      n = n / 10;
    }
  return (i);
}
