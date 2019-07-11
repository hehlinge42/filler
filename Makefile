# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 21:32:05 by sikpenou          #+#    #+#              #
#    Updated: 2019/07/10 19:20:35 by sikpenou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

#CFLAGS = -Wall -Wextra -Werror
CFLAGS = -g

NAME = libftprintf.a

EXEC = ft_printf

SRCS = $(addprefix $(SRCDIR), $(SRCFILES))

SRCFILES = \
		   ft_printf.c \
		   core.c \
		   memory.c \
		   support.c \
		   display.c \
		   text_funcs.c \
		   num_funcs.c \
		   floats.c \
		   calc_floats.c \
		   padding.c \
		   debug.c

SRCDIR = ./srcs/

OBJS = $(addprefix $(OBJDIR), $(OBJFILES))

OBJFILES = $(SRCFILES:.c=.o)

OBJDIR = ./objs/

INCLS = $(INCLDIR)*.h

INCLDIR = ./includes/

MAIN = ./srcs/main.c

LIB = libftprintf.a

LIBDIR = ./

all: $(NAME) $(EXEC)
	@echo "\e[31mDEPENDENCY TO EXEC TO BE REMOVED\e[0m"

$(NAME): $(INCLS) $(SRCS)
#
	@rm -f auteur
	@echo sikpenou > auteur
	@/bin/echo compiling source files
	@make -j --no-print-directory objects
	@/bin/echo creating $(LIBDIR)$(LIB)
	@ar src $(LIBDIR)$(LIB) $(OBJS)

ft_printf: $(MAIN) $(LIB)
#
	@/bin/echo updating $(NAME)
	@make -j --no-print-directory $(NAME)
	@/bin/echo linking main and $(LIBDIR)$(LIB)
	@$(CC) $(CFLAGS) -I $(INCLDIR) -o ./objs/main.o -c ./srcs/main.c
	@$(CC) $(CFLAGS) -I $(INCLDIR) -L$(LIBDIR) -o $@ ./objs/main.o -lftprintf
#	@clear

objects: $(OBJS)

$(OBJDIR)%.o: $(SRCDIR)%.c
#
	@$(CC) $(CFLAGS) -I $(INCLDIR) -o $@ -c $<

test: $(INCL) testprintf.c
#
	@$(CC) $(CFLAGS) -I $(INCLDIR) -L$(LIBDIR) -o $@ testprintf.c -lftprintf

clean: FORCE
#
	@rm -f $(OBJS)
	@echo "\e[31mlibft clean up - erase this and libft folder before push\e[0m"
	@rm -f ./libft/*.o
	@rm -f "./objs/main.o"
	@echo "rm -f .o files"

fclean: clean
#
	@rm -f a.out
	@rm -f test
	rm -f $(NAME)
	rm -f ft_printf

re: FORCE
#
	@make -j --no-print-directory fclean
	@make -j --no-print-directory all

FORCE:
