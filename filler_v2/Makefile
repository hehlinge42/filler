# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 21:32:05 by sikpenou          #+#    #+#              #
#    Updated: 2019/08/02 14:36:43 by sikpenou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

NAME = hehlinge.filler

SRCS = $(addprefix $(SRCDIR), $(SRCFILES))

SRCFILES =	main.c				\
			support.c			\
			parser.c			\
			debug.c				\
			points.c			\

SRCDIR = ./srcs/

OBJS = $(addprefix $(OBJDIR), $(OBJFILES))

OBJFILES = $(SRCFILES:.c=.o)

OBJDIR = objs/

INCLS = includes/

LIB = libft.a

LIBINCLS =  $(LIBDIR)$(INCLS)

LIBDIR = libft/

all: $(NAME)

$(NAME): $(INCLS) $(SRCS) $(LIB)
#
	@rm -f auteur
	@echo hehlinge > auteur
	@/bin/echo compiling source files
	@mkdir -p objs
	@make -j --no-print-directory objects
	@$(CC) $(CFLAGS) -I $(INCLS) -o $@ $(OBJS) $(LIBDIR)/$(LIB)
#	@clear

$(LIB):
	make -j --no-print-directory -C $(LIBDIR)

objects: $(OBJS)

$(OBJDIR)%.o: $(SRCDIR)%.c
#
	@$(CC) $(CFLAGS) -I $(INCLS) -I $(LIBINCLS) -o $@ -c $<

clean: FORCE
#
	@rm -f $(OBJS)
#	@rm -f "./objs/main.o"
	make clean -j --no-print-directory -C $(LIBDIR)
	@echo "rm -f .o files"
	@rm -f $(OBJS)

fclean: clean
#
	@rm -f a.out
	@rm -f test
	rm -f libft/libft.a
	rm -f $(NAME)

re: FORCE
#
	@make -j --no-print-directory fclean
	@make -j --no-print-directory all

FORCE:
