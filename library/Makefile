#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 13:41:38 by jcarra            #+#    #+#              #
#    Updated: 2017/04/04 10:42:47 by jcarra           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME			=	libft.a

SRC_PART1		=	ft_strcmp.c \
					ft_strncmp.c \
					ft_strcmp_case.c \
					ft_strchr.c \
					ft_strlchr.c \
					ft_strrchr.c \
					ft_strlen.c \
					ft_strdup.c \
					ft_atoi.c \
					ft_strstr.c \
					ft_strnstr.c \
					ft_memset.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_isalpha.c \
					ft_isdigit.c \
					ft_isalnum.c \
					ft_isprint.c \
					ft_isascii.c \
					ft_isoct.c \
					ft_ishex.c

SRC_PART2		=   ft_esc_hex.c \
                    ft_eval_esc.c \
                    ft_evaluator.c \
                    ft_memalloc.c \
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

SRC_BTREE		=	btree_create_node.c \
					btree_insert_data.c \
					btree_add_node.c \
					btree_apply_infix.c \
					btree_apply_prefix.c \
					btree_apply_suffix.c

SRC_LIST		=	ft_create_elem.c \
					ft_list_push_back.c \
					ft_list_push_front.c \
					ft_list_size.c \
					ft_list_last.c \
					ft_list_push_params.c \
					ft_list_clear.c \
					ft_list_at.c \
					ft_list_reverse.c \
					ft_list_foreach.c \
					ft_list_del.c \
					ft_list_sort.c

SRC_GNL			=	get_next_line.c

DIRSRC_PART1	=	Part_1/
DIRSRC_PART2	=	Part_2/
DIRSRC_BTREE	=	Btree/
DIRSRC_LIST		=	List/
DIRSRC_GNL		=	GetNextLine/
DIRINC			=	include/

PART1			=	$(SRC_PART1:%=$(DIRSRC_PART1)%)
PART2			=	$(SRC_PART2:%=$(DIRSRC_PART2)%)
BTREE			=	$(SRC_BTREE:%=$(DIRSRC_BTREE)%)
LIST			=	$(SRC_LIST:%=$(DIRSRC_LIST)%)
GNL				=	$(SRC_GNL:%=$(DIRSRC_GNL)%)
OBJS_PART1		=	$(PART1:.c=.o)
OBJS_PART2		=	$(PART2:.c=.o)
OBJS_BTREE		=	$(BTREE:.c=.o)
OBJS_LIST		=	$(LIST:.c=.o)
OBJS_GNL		=	$(GNL:.c=.o)

CFLAGS			=	-Wall -Wextra -I./$(DIRINC) -g3

CC				=	gcc
LIB				=	ar rc
RM				=	rm -f
ECHO			=	printf


all		:		$(NAME)
				@$(ECHO) '\033[32m>\033[0m libft : [\033[34mAll\033[0m] ->\033[32m	Ready\n\033[0m'

$(NAME)	:		.part1 .part2 .part3 .part4 .part5
				@$(LIB) $(NAME) $(OBJS_PART1) $(OBJS_PART2) $(OBJS_BTREE) $(OBJS_LIST) $(OBJS_GNL)

%.o		:	%.c
			@$(CC) -o $@ -c $< $(CFLAGS)
			@$(ECHO) '-> \033[36m$@\033[0m\n'

.part1:			$(OBJS_PART1)
				@touch .part1
				@chmod 755 .part1
				@$(ECHO) '\033[32m>\033[0m libft : [\033[35mPart 1\033[0m] ->\033[32m	Ready\n\033[0m'

.part2:			$(OBJS_PART2)
				@touch .part2
				@chmod 755 .part2
				@$(ECHO) '\033[32m>\033[0m libft : [\033[35mPart 2\033[0m] ->\033[32m	Ready\n\033[0m'

.part3:			$(OBJS_BTREE)
				@touch .part3
				@chmod 755 .part3
				@$(ECHO) '\033[32m>\033[0m libft : [\033[35mBtree\033[0m] ->\033[32m	Ready\n\033[0m'

.part4:			$(OBJS_LIST)
				@touch .part4
				@chmod 755 .part4
				@$(ECHO) '\033[32m>\033[0m libft : [\033[35mList\033[0m] ->\033[32m	Ready\n\033[0m'

.part5:			$(OBJS_GNL)
				@touch .part5
				@chmod 755 .part5
				@$(ECHO) '\033[32m>\033[0m libft : [\033[35mGnl\033[0m] ->\033[32m	Ready\n\033[0m'

clean	:
				@$(RM) $(OBJS_PART1) $(OBJS_PART2) $(OBJS_BTREE) $(OBJS_LIST) $(OBJS_GNL) .part1 .part2 .part3 .part4 .part5
				@$(ECHO) '\033[31m>\033[0m libft : \033[31mDirectory cleaned\n\033[0m'

fclean	:		clean
				@$(RM) $(NAME)
				@$(ECHO) '\033[31m>\033[0m libft : \033[31mRemove executable\n\033[0m'

re		:		fclean all

.PHONY	:		all clean fclean re
