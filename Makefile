# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 21:32:05 by sikpenou          #+#    #+#              #
#    Updated: 2019/08/19 17:51:02 by sikpenou         ###   ########.fr        #
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
			avail.c				\
			algo.c

SRCDIR = ./srcs/

OBJS = $(addprefix $(OBJDIR), $(OBJFILES))

OBJFILES = $(SRCFILES:.c=.o)

OBJDIR = objs/

INCLS = includes/

LIB = libft.a

LIBINCLS =  $(LIBDIR)$(INCLS)

LIBDIR = libft/

LIBFTPRINTF = libftprintf.a

LIBFTPRINTFDIR = libft/ft_printf

all: $(NAME)

$(NAME): $(INCLS) $(SRCS) $(LIB) $(LIBFTPRINTF)
	@rm -f auteur
	@echo hehlinge > auteur
	@/bin/echo compiling source files
	@mkdir -p objs
	@make -j --no-print-directory objects
	@$(CC) $(CFLAGS) -I $(INCLS) -o $@ $(OBJS) $(LIBDIR)/$(LIB) $(LIBFTPRINTFDIR)/$(LIBFTPRINTF)

$(LIB):
	@make -j --no-print-directory -C $(LIBDIR)

$(LIBFTPRINTF):
	@make -j --no-print-directory -C $(LIBFTPRINTFDIR)

objects: $(OBJS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -I $(INCLS) -I $(LIBINCLS) -o $@ -c $<

clean: FORCE
	@rm -f $(OBJS)
	@make clean -j --no-print-directory -C $(LIBDIR)
	@make clean -j --no-print-directory -C $(LIBFTPRINTFDIR)
	@echo "rm -f .o files"
	@rm -f $(OBJS)

fclean: clean
	@rm -f a.out
	@rm -f test
	rm -f libft/libft.a
	rm -f $(LIBFPRINTFDIR)$(LIBFTPRINTF)
	rm -f $(NAME)

re: FORCE
	@make -j --no-print-directory fclean
	@make -j --no-print-directory all

FORCE:
