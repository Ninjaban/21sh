/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 13:36:40 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/24 10:58:25 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

# include <unistd.h>

# include "ft_btree.h"
# include "ft_is.h"
# include "ft_lst.h"
# include "ft_mem.h"
# include "ft_put.h"
# include "ft_str.h"

# define ABS(x) (x < 0 ? -x : x)
# define MAX(x, y) (x > y ? x : y)
# define MIN(x, y) (x < y ? x : y)

int					ft_toupper(int c);
int					ft_tolower(int c);

int					ft_atoi(const char *str);
char				*ft_itoa(int n);

int					ft_match(char *s1, char *s2);

#endif
