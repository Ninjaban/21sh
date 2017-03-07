#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 13:36:54 by mrajaona          #+#    #+#              #
#    Updated: 2017/02/27 16:15:28 by mrajaona         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	libft.a
DIRSRC		=	./sources/
INCLUDE		=	./includes/

DIR_BTREE	=	btree/
SRC_BTREE	=	btree_apply_infix.c \
				btree_apply_prefix.c \
				btree_apply_suffix.c \
				btree_create_node.c \
				btree_insert_data.c \
				btree_search_item.c
SRCS_BTREE	=	$(addprefix $(DIR_BTREE), $(SRC_BTREE))

DIR_IS		=	ft_is/
SRC_IS		=	ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isblank.c \
				ft_isdigit.c \
				ft_ishex.c \
				ft_isoct.c \
				ft_isprint.c \
				ft_iswspace.c
SRCS_IS		=	$(addprefix $(DIR_IS), $(SRC_IS))

DIR_LST		=	ft_lst/
SRC_LST		=	ft_del.c \
				ft_lstadd.c \
				ft_lstadd_end.c \
				ft_lstadd_ascii.c \
				ft_lstdel.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstswap.c
SRCS_LST	=	$(addprefix $(DIR_LST), $(SRC_LST))

DIR_MEM		=	ft_mem/
SRC_MEM		=	ft_bzero.c \
				ft_memalloc.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memdel.c \
				ft_memmove.c \
				ft_memset.c
SRCS_MEM	=	$(addprefix $(DIR_MEM), $(SRC_MEM))

DIR_PUT		=	ft_put/
SRC_PUT		=	ft_putchar.c \
				ft_putchar_fd.c \
				ft_putendl.c \
				ft_putendl_fd.c \
				ft_putnbr.c \
				ft_putnbr_fd.c \
				ft_putstr.c \
				ft_putstr_fd.c
SRCS_PUT	=	$(addprefix $(DIR_PUT), $(SRC_PUT))

DIR_STR		=	ft_str/
SRC_STR		=	ft_strcat.c \
				ft_strchr.c \
				ft_strcjoin.c \
				ft_strclr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdel.c \
				ft_strdup.c \
				ft_strequ.c \
				ft_striter.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlen.c \
				ft_strmap.c \
				ft_strmapi.c \
				ft_strncat.c \
				ft_strncmp.c \
				ft_strncpy.c \
				ft_strnequ.c \
				ft_strnew.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strsplit.c \
				ft_strstr.c \
				ft_strsub.c \
				ft_strtrim.c
SRCS_STR	=	$(addprefix $(DIR_STR), $(SRC_STR))

SRC_GNL		=	get_next_line.c

SRC_ELSE	=	ft_atoi.c \
				ft_itoa.c \
				ft_match.c \
				ft_tolower.c \
				ft_toupper.c

SRC			=	$(SRC_BTREE) $(SRC_IS) $(SRC_LST) $(SRC_MEM) $(SRC_PUT) \
				$(SRC_STR) $(SRC_GNL)  $(SRC_ELSE)

SRCSS		=	$(SRCS_BTREE) $(SRCS_IS) $(SRCS_LST) $(SRCS_MEM) $(SRCS_PUT) \
				$(SRCS_STR) $(SRC_GNL)  $(SRC_ELSE)

SRCS		=	$(addprefix $(DIRSRC), $(SRCSS))

OBJ			=	$(SRC:.c=.o)
OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror -I $(INCLUDE)

CC			=	/usr/bin/gcc
RM			=	/bin/rm -f
ECHO		=	/bin/echo -e

all		:		$(NAME)

$(NAME)	:		$(SRCS) $(INCLUDE) $(OBJS)
				ar rc $(NAME) $(OBJS)
				ranlib $(NAME)
				@$(ECHO) '> Compiled'

clean	:
				@$(RM) $(OBJS)
				@$(ECHO) '> Directory cleaned'

fclean	:		clean
				@$(RM) $(NAME)
				@$(ECHO) '> Removed executable'

re		:		fclean all

.PHONY	:		all clean fclean re

.DEFAULT_GOAL := all