##
## Makefile for  in /home/carra_j/rendu/Igraf
## 
## Made by carra Jonathan
## Login   <carra_j@epitech.net>
## 
## Started on  Mon Nov 10 09:22:09 2014 carra Jonathan
## Last update Fri Jan 22 15:16:38 2016 Jonathan Carra
##

CC		= gcc

RM		= rm -f

CFLAGS		= -Wextra -Wall -ansi -pedantic -I.

NAME		= terms

SRCS		= sources/my_putchar.c \
		  sources/my_putstr.c \
		  sources/my_putnbr.c \
		  sources/my_getnbr.c \
		  sources/my_revnbr.c \
		  sources/my_strlen.c \
		  sources/my_write.c \
		  sources/my_read.c \
		  my_ls.c \
		  totab.c \
		  recup_ligne.c \
		  my_select.c \
		  qsort.c \
		  my_aff.c \
		  create.c \
		  my_free.c \
		  main.c

OBJS		= $(SRCS:.c=.o)

LDFLAGS		= -lncurses

all: 		$(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

.PHONY:		all clean fclean re
