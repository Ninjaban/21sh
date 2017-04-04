#  **************************************************************************  #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarra <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/01 00:00:00 by jcarra            #+#    #+#              #
#    Updated: 2017/01/01 00:00:00 by jcarra           ###   ########.fr        #
#                                                                              #
#  **************************************************************************  #

NAME		=	21sh

SRC		=	ft_access.c \
			ft_alias.c \
			ft_alias_init.c \
			ft_builtins.c \
			ft_chdir.c \
			ft_chdir_cdpath.c \
			ft_chdir_opt.c \
			ft_chdir_tools.c \
			ft_chdir_trim.c \
			ft_completion.c \
			ft_completion_norme.c \
			ft_completion_tools.c \
			ft_delchar.c \
			ft_echo.c \
			ft_env.c \
			ft_error.c \
			ft_exec.c \
			ft_exec_child.c \
			ft_exec_init.c \
			ft_export.c \
			ft_free.c \
			ft_gestion_error.c \
			ft_gestion_error_redir.c \
			ft_help.c \
			ft_hist_find.c \
			ft_hist_str.c \
			ft_history.c \
			ft_history_builtin.c \
			ft_history_tools.c \
			ft_init.c \
			ft_keymap.c \
			ft_keymap_tools.c \
			ft_main.c \
			ft_parsing.c \
			ft_parsing_cmd.c \
			ft_parsing_init.c \
			ft_parsing_node.c \
			ft_parsing_parenthesis.c \
			ft_parsing_semicolon.c \
			ft_parsing_split.c \
			ft_parsing_split_tools.c \
			ft_parsing_tools.c \
			ft_path.c \
			ft_prompt.c \
			ft_prompt_path.c \
			ft_read.c \
			ft_read_check.c \
			ft_read_copy.c \
			ft_read_move.c \
			ft_read_print.c \
			ft_set.c \
			ft_setenv.c \
			ft_shell.c \
			ft_shell_excl.c \
			ft_shell_norme.c \
			ft_shell_shrc.c \
			ft_signal.c \
			ft_sys.c \
			ft_unalias.c \
			ft_unset.c \
			ft_unset_tools.c \
			ft_unsetenv.c \
			ft_varenv.c \
			match.c

LIB		=	libft.a

DIRSRC		=	sources/
DIRINC		=	include/
DIRLIB		=	library/

SRCS		=	$(SRC:%=$(DIRSRC)%)
LIBS		=	$(LIB:%=$(DIRLIB)%)

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror -I./$(DIRINC) -I./$(DIRLIB)$(DIRINC)
LFLAGS		=	-lncurses

CC		=	gcc
RM		=	rm -f
ECHO		=	printf
MAKE		=	make -C


all		:	$(NAME)
			@$(ECHO) '\033[32m>\033[0m $(NAME) : [\033[34mAll\033[0m] ->\033[32m\tReady\n\033[0m'
$(NAME)		:	.libft .hide
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(LFLAGS)

.hide		:	$(OBJS)
			@touch .hide
			@chmod 755 .hide
			@$(ECHO) '\033[32m>\033[0m $(NAME) : [\033[33mSources\033[0m] ->\033[32m	Ready\n\033[0m'

.libft		:
			@touch .libft
			@chmod 755 .libft
			@$(MAKE) $(DIRLIB)

clean		:
			@$(MAKE) $(DIRLIB) fclean
			@$(RM) $(OBJS) .hide .libft
			@$(ECHO) '\033[31m>\033[0m $(NAME) : \033[31mDirectory cleaned\n\033[0m'

fclean		:	clean
			@$(RM) $(NAME)
			@$(ECHO) '\033[31m>\033[0m $(NAME) : \033[31mRemove executable\n\033[0m'

re		:	fclean all

.PHONY		:	all clean fclean re

