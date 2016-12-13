/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 13:23:35 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/13 10:06:01 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define ABS(Value) ((Value < 0) ? Value * -1 : Value)

# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"

/*
**	Structure
*/

typedef struct		s_lst
{
	struct s_lst	*next;
	void			*data;
}					t_lst;

/*
**	Part 1
*/

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(char *str);
char				*ft_strdup(char *src);
char				*ft_strstr(const char *str, const char *src);
char				*ft_strnstr(const char *str, const char *src, size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
size_t				ft_strlen(const char *str);

/*
**	Part 2
*/

void				ft_memdel(void **ap);
void				ft_strclr(char *s);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar(char c);
void				ft_putnbr(int nbr);
void				ft_putendl(char *str);
void				ft_putstr(char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int nbr, int fd);
void				ft_putendl_fd(char *str, int fd);
void				ft_putstr_fd(char *str, int fd);
void				*ft_memalloc(size_t size);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strnew(size_t size);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
char				*ft_itoa(int n);
char				*ft_revstr(char *str);
char				**ft_strsplit(char const *s, char const *c);
char				*ft_revstr(char *str);
size_t				ft_tablen(char **tab);
unsigned long int	ft_revnbr(unsigned long int nbr);

/*
**	Bonus
*/

t_lst				*ft_create_elem(void *data);
void				ft_list_push_back(t_lst **begin_list, void *data);
void				ft_list_push_front(t_lst **begin_list, void *data);
int					ft_list_size(t_lst *begin_list);
t_lst				*ft_list_last(t_lst *begin_list);
t_lst				*ft_list_push_params(int ac, char **av);
void				ft_list_clear(t_lst **begin_list);
t_lst				*ft_list_at(t_lst *begin_list, unsigned int nbr);
void				ft_list_reverse(t_lst **begin_list);
void				ft_list_foreach(t_lst *begin_list, void (*f)(void *));

#endif
