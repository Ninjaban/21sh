/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 14:24:26 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/16 19:41:08 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "terms.h"

/*
**	clear	=	efface l'ecran.
**	vi		=	curseur invisible.
**	ve		=	curseur visible.
**	cm		=	deplacer le curseur.
**	us		=	debut souligner.
**	ue		=	fin souligner.
*/

int			fputchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int			ft_termcaps_change(struct termios *term)
{
	if (tcsetattr(0, TCSANOW, &(*term)) == -1)
		return (FALSE);
	return (TRUE);
}

int			ft_termcaps_init(struct termios *term, struct termios *save)
{
	const char		*name;

	if ((name = getenv("TERM")) == NULL)
		return (FALSE);
	if (tgetent(NULL, name) != 1)
		return (FALSE);
	if (tcgetattr(0, &(*term)) == -1)
		return (FALSE);
	if (tcgetattr(0, &(*save)) == -1)
		return (FALSE);
	(*term).c_lflag &= ~(ICANON);
	(*term).c_lflag &= ~(ECHO);
	return (TRUE);
}
