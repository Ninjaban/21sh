/*
** main.c for  in /home/carra_j/Archive/base
** 
** Made by carra Jonathan
** Login   <carra_j@epitech.net>
** 
** Started on  Fri Jan 16 12:05:26 2015 carra Jonathan
** Last update Wed Oct 28 14:29:03 2015 Jonathan Carra
*/

#include <term.h>
#include "include/my.h"

void    end(t_sh save)
{
  struct termios        terms;

  save.free_log = 1;
  save.free_action = 1;
  save.free_name = 1;
  if (save.save != NULL)
    save.free_save = 1;
  free_all(NULL, NULL, save);
  cursergoto("ve", 1, 1);
  if (tcgetattr(0, &terms) == -1)
    exit(-1);
  terms.c_lflag = (ICANON | ECHO);
  if (tcsetattr(0, 0, &terms) == -1)
    exit(-1);
  exit(0);
}


int	fputchar(int c)
{
  write(1, &c, 1);
  return (0);
}

/*
 * clear = efface l'écrans
 * civis = curseur invisible
 * cnorm = curseur normal
 * cm = déplacer le curseur
 * us = commencer le soulignement
 * ue = arrêter le soulignement
 */
int	cursergoto(char *cmd, int colone, int line)
{
  char	*str;

  str = tgoto(tgetstr(cmd, NULL), colone, line);
  tputs(str, 1, fputchar);
  return (0);
}

int     voir_touche(int pos, int lenght, int nbr_sep, int *select)
{
  char  buffer[4];

  while (42)
    {
      read(0, buffer, 3);
      if (buffer[0] == 122 || (buffer[0] == 27 && buffer[2] == 65))
	{
	  if (pos - nbr_sep >= 0)
	    return (pos - nbr_sep);
	  else
	    {
	      while (pos + nbr_sep < lenght)
		pos = pos + nbr_sep;
	      return (pos);
	    }
	}
      else if (buffer[0] == 115 || (buffer[0] == 27 && buffer[2] == 66))
	{
	  if (pos + nbr_sep < lenght)
	    return (pos + nbr_sep);
	  else
	    {
	      while (pos >= nbr_sep)
		pos = pos - (nbr_sep);
	      return (pos);
	    }
	}
      else if (buffer[0] == 100 || (buffer[0] == 27 && buffer[2] == 67))
	{
	  if (pos + 1 < lenght)
	    return (pos + 1);
	  else
	    return (0);
	}
      else if (buffer[0] == 113 || (buffer[0] == 27 && buffer[2] == 68))
	{
	  if (pos - 1 < 0)
	    return (lenght - 1);
	  else
	    return (pos - 1);
	}
      else if (buffer[0] == '\E')
	return (-2);
      else if (buffer[0] == 127)
	{
	  select[pos] = 3;
	  return (pos);
	}
      else if (buffer[0] == 3)
	{
	  select_copier(select, pos, lenght);
	  return (pos);
	}
      else if (buffer[0] == 24)
        {
          select_couper(select, pos, lenght);
          return (pos);
        }
      else if (buffer[0] == 22)
        {
          select[pos] = 6;
          return (pos);
        }
      else if (buffer[0] == 32)
	{
	  if (select[pos] == 0)
	    select[pos] = 1;
	  else
	    select[pos] = 0;
	  return (pos);
	}
      else if (buffer[0] == 10)
	{
	  select[pos] = 2;
	  return (pos);
	}
      else if (buffer[0] == 14)
	return (-3);
    }
  return (pos);
}

int	main()
{
  struct termios	term;
  const char		*name_term;
  char			*str;
  t_sh			save;

  if ((name_term = getenv("TERM")) == NULL)
    return (-1);
  if (tgetent(NULL, name_term) != 1)
    return (-1);
  if (tcgetattr(0, &term) == -1)
    return (-1);

  term.c_lflag &= ~(ICANON);
  term.c_lflag &= ~(ECHO);
  term.c_lflag &= ~(ISIG);

  if (tcsetattr(0, TCSADRAIN, &term) == -1)
    return (-1);

  cursergoto("vi", 1, 1);

  save.save = NULL;
  save.action = NULL;
  save.log = NULL;
  save.free_save = 0;
  save.free_log = 0;
  save.free_action = 0;
  save.free_name = 0;
  if ((save.name = malloc(sizeof(char) * 2)) == NULL)
    return (-1);
  save.name[0] = '.';
  save.name[1] = '\0';
  str = my_ls(".");

  if (my_select(str, save) == -1)
    {
      my_putstr("Une erreur est survenu.\n");
      end(save);
    }
  return (0);
}
