#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 13:41:38 by jcarra            #+#    #+#              #
#    Updated: 2016/12/12 15:22:03 by jcarra           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME			=	libft.a

SRC_PART1		=	ft_strcmp.c \
					ft_strncmp.c \
					ft_strchr.c \
					ft_strrchr.c \
					ft_strlen.c \
					ft_strdup.c \
					ft_atoi.c \
					ft_strstr.c \
					ft_strnstr.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_isalpha.c \
					ft_isdigit.c \
					ft_isalnum.c \
					ft_isprint.c \
					ft_isascii.c

SRC_PART2		=	ft_memalloc.c \
					ft_memdel.c \
					ft_strclr.c \
					ft_strdel.c \
					ft_strequ.c \
					ft_striter.c \
					ft_striteri.c \
					ft_strjoin.c \
					ft_strmap.c \
					ft_strmapi.c \
					ft_strnequ.c \
					ft_strnew.c \
					ft_strsub.c \
					ft_strtrim.c \
					ft_putchar.c \
					ft_putstr.c \
					ft_putnbr.c \
					ft_putendl.c \
					ft_putchar_fd.c \
					ft_putstr_fd.c \
					ft_putnbr_fd.c \
					ft_putendl_fd.c \
					ft_strsplit.c \
					ft_itoa.c \
					ft_revnbr.c \
					ft_revstr.c \
					ft_tablen.c

SRC_BONUS		=	ft_create_elem.c \
					ft_list_push_back.c \
					ft_list_push_front.c \
					ft_list_size.c \
					ft_list_last.c \
					ft_list_push_params.c \
					ft_list_clear.c \
					ft_list_at.c \
					ft_list_reverse.c \
					ft_list_foreach.c

SRC_GNL			=	get_next_line.c

DIRSRC_PART1	=	Part\ 1/
DIRSRC_PART2	=	Part\ 2/
DIRSRC_BONUS	=	Bonus/
DIRSRC_GNL		=	GetNextLine/
DIRINC			=	include/

PART1			=	$(SRC_PART1:%=$(DIRSRC_PART1)%)
PART2			=	$(SRC_PART2:%=$(DIRSRC_PART2)%)
BONUS			=	$(SRC_BONUS:%=$(DIRSRC_BONUS)%)
GNL				=	$(SRC_GNL:%=$(DIRSRC_GNL)%)
OBJS_PART1		=	$(SRC_PART1:.c=.o)
OBJS_PART2		=	$(SRC_PART2:.c=.o)
OBJS_BONUS		=	$(SRC_BONUS:.c=.o)
OBJS_GNL		=	$(SRC_GNL:.c=.o)

CFLAGS			=	-Wall -Wextra -I./$(DIRINC)

CC				=	gcc
LIB				=	ar rc
RM				=	rm -f
ECHO			=	printf


all		:		$(NAME)

$(NAME)	:
				@$(CC) $(CFLAGS) -c $(PART1) $(PART2) $(BONUS) $(GNL)
				@$(LIB) $(NAME) $(OBJS_PART1) $(OBJS_PART2) $(OBJS_BONUS) $(OBJS_GNL)
				@$(ECHO) '\033[32m> libft : Compiled\n\033[0m'

part1 :
				@$(CC) $(CFLAGS) -c $(PART1)
				@$(LIB) $(NAME) $(OBJS_PART1)
				@$(ECHO) '\033[32m> libft - Part 1 : Compiled\n\033[0m'

part2 :
				@$(CC) $(CFLAGS) -c $(PART2)
				@$(LIB) $(NAME) $(OBJS_PART2)
				@$(ECHO) '\033[32m> libft - Part 2 : Compiled\n\033[0m'

bonus :
				@$(CC) $(CFLAGS) -c $(BONUS)
				@$(LIB) $(NAME) $(OBJS_BONUS)
				@$(ECHO) '\033[32m> libft - Bonus : Compiled\n\033[0m'

gnl:
				@$(CC) $(CFLAGS) -c $(GNL)
				@$(LIB) $(NAME) $(OBJS_GNL)
				@$(ECHO) '\033[32m> libft - GetNextLine : Compiled\n\033[0m'

clean	:
				@$(RM) $(OBJS_PART1) $(OBJS_PART2) $(OBJS_BONUS) $(OBJS_GNL)
				@$(ECHO) '\033[31m> libft : Directory cleaned\n\033[0m'

fclean	:		clean
				@$(RM) $(NAME)
				@$(ECHO) '\033[31m> libft : Remove executable\n\033[0m'

re		:		fclean all

.PHONY	:		all part1 part2 bonus gnl clean fclean re
