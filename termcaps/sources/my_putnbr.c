/*
** my_put_nbr.c for my_put_nbr.c in /home/carra_j/rendu
** 
** Made by carra Jonathan
** Login   <carra_j@epitech.net>
** 
** Started on  Thu Oct  2 08:27:05 2014 carra Jonathan
** Last update Sat Jun 20 08:48:33 2015 carra Jonathan
*/

#include "include/my.h"

void	my_putnbr(int nbr)
{
  int	n;

  if (nbr == 0)
    my_putchar('0');
  if (nbr < 0)
    {
      my_putchar('-');
      nbr = nbr * -1;
    }
  nbr = my_revnbr(nbr);
  while (nbr != 1)
    {
      n = nbr % 10;
      nbr = nbr / 10;
      my_putchar(n + 48);
    }
}
