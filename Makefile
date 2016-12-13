#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/16 09:04:55 by jcarra            #+#    #+#              #
#    Updated: 2016/12/12 09:28:55 by jcarra           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	minishell

SRC			=	ft_varenv.c \
				ft_sys.c \
				ft_delchar.c \
				ft_unalias.c \
				ft_alias.c \
				ft_history.c \
				ft_prompt_path.c \
				ft_prompt.c \
				ft_chdir_tools.c \
				ft_chdir.c \
				ft_unsetenv.c \
				ft_setenv.c \
				ft_env.c \
				ft_echo.c \
				ft_path.c \
				ft_access.c \
				ft_exec.c \
				ft_gestion_error.c \
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
OBJS		=	$(SRC:.c=.o)
LIBS		=	$(LIB:%=$(DIRLIB)%)

CFLAGS		=	-Wall -Wextra -Werror -I./$(DIRINC) -I./$(DIRLIB)$(DIRINC) -g3
LFLAGS		=

CC			=	gcc
RM			=	rm -f
ECHO		=	printf
MAKE		=	make -C


all		:		$(NAME)

$(NAME)	:
				@$(MAKE) $(DIRLIB)
				@$(CC) $(CFLAGS) -c $(SRCS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(LFLAGS)
				@$(ECHO) '\033[32m> Compiled\n\033[0m'

clean	:
				@$(MAKE) $(DIRLIB) clean
				@$(RM) $(OBJS)
				@$(ECHO) '\033[31m> Directory cleaned\n\033[0m'

fclean	:		clean
				@$(MAKE) $(DIRLIB) fclean
				@$(RM) $(NAME)
				@$(ECHO) '\033[31m> Remove executable\n\033[0m'

re		:		fclean all

.PHONY	:		all clean fclean re
