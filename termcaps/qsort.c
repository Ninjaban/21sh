/*
** qsort.c for  in /home/jonathan/rendu/termcaps
** 
** Made by Jonathan Carra
** Login   <jonathan@epitech.net>
** 
** Started on  Thu Oct 22 11:56:10 2015 Jonathan Carra
** Last update Thu Oct 22 14:43:52 2015 Jonathan Carra
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "include/my.h"

/* qsort C-string comparison function */ 
int cstring_cmp(const void *a, const void *b) 
{ 
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;
  return strcmp(*ia, *ib);
  /* strcmp functions works exactly as expected from
     comparison function */ 
} 
 
/* C-string array printing function */ 
void print_cstring_array(char **array, size_t len) 
{ 
  size_t i;

  for(i=0; i<len; i++) 
    {
      my_putstr(array[i]);
      my_putstr(" | ");
    }
  my_putchar('\n');
} 

/* sorting C-strings array using qsort() example */ 
void sort_cstrings(char *strings[], int len) 
{ 
  /*  char *strings[] = { "Zorro", "Alex", "Celine", "Bill", "Forest", "Dexter" };*/

  /* print original string array */ 
  /* print_cstring_array(strings, len);*/
 
  /* sort array using qsort functions */ 
  qsort(strings, len, sizeof(char *), cstring_cmp);
 
  /* print sorted string array */ 
  /* print_cstring_array(strings, len);*/
}
