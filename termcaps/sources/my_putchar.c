/*
** my_putchar.c for  in /home/carra_j/rendu/CPE_2014_bsq
** 
** Made by carra Jonathan
** Login   <carra_j@epitech.net>
** 
** Started on  Mon Dec 15 10:50:37 2014 carra Jonathan
** Last update Sat Jun 20 08:47:06 2015 carra Jonathan
*/

#include "include/my.h"

void	my_putchar(char c)
{
  write(1, &c, 1);
}
