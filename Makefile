#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/20 15:07:26 by jcarra            #+#    #+#              #
#    Updated: 2017/01/24 10:52:00 by jcarra           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	21sh

SRC			=	match.c \
				ft_completion.c \
				ft_read.c \
				ft_history.c \
				ft_init.c \
				ft_gestion_error.c \
				ft_path.c \
				ft_varenv.c \
				ft_delchar.c \
				ft_sys.c \
				ft_setenv.c \
				ft_chdir_tools.c \
				ft_prompt_path.c \
				ft_prompt.c \
				ft_error.c \
				ft_free.c \
				ft_parsing_tools.c \
				ft_parsing.c \
				ft_shell.c \
				ft_main.c

LIB			=	libft.a

DIRSRC		=	sources/
DIRINC		=	include/
DIRLIB		=	library/

SRCS		=	$(SRC:%=$(DIRSRC)%)
LIBS		=	$(LIB:%=$(DIRLIB)%)

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror -I./$(DIRINC) -I./$(DIRLIB)$(DIRINC)
LFLAGS		=	-lncurses

CC			=	gcc
RM			=	rm -f
ECHO		=	printf
MAKE		=	make -C


all		:		$(NAME)
				@$(ECHO) '\033[32m>\033[0m $(NAME) : [\033[34mAll\033[0m] ->\033[32m	Ready\n\033[0m'

$(NAME)	:		.libft .hide
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(LFLAGS)

.hide	:		$(OBJS)
				@touch .hide
				@chmod 755 .hide
				@$(ECHO) '\033[32m>\033[0m $(NAME) : [\033[33mSources\033[0m] ->\033[32m	Ready\n\033[0m'

.libft	:
				@touch .libft
				@chmod 755 .libft
				@$(MAKE) $(DIRLIB)

clean	:
				@$(MAKE) $(DIRLIB) fclean
				@$(RM) $(OBJS) .hide .libft
				@$(ECHO) '\033[31m>\033[0m $(NAME) : \033[31mDirectory cleaned\n\033[0m'

fclean	:		clean
				@$(RM) $(NAME)
				@$(ECHO) '\033[31m>\033[0m $(NAME) : \033[31mRemove executable\n\033[0m'

re		:		fclean all

.PHONY	:		all clean fclean re
