/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:46:21 by mrajaona          #+#    #+#             */
/*   Updated: 2016/12/22 11:08:52 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

/*
** max read 4096
*/

# define BUFF_SIZE 20
# define NB_FD 10
# define ENDL '\n'

typedef struct	s_line
{
	int				fd;
	char			str[BUFF_SIZE + 1];
	int				size;
}				t_line;

int				get_next_line(const int fd, char **line);

#endif
