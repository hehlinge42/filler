# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 21:32:05 by sikpenou          #+#    #+#              #
#    Updated: 2019/07/11 17:46:23 by hehlinge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = hehlinge.filler

SRCS = $(addprefix $(SRCDIR), $(SRCFILES))

SRCFILES = main.c	parser.c

SRCDIR = ./srcs/

OBJS = $(addprefix $(OBJDIR), $(OBJFILES))

OBJFILES = $(SRCFILES:.c=.o)

OBJDIR = ./objs/

INCLS = $(INCLDIR)*.h

INCLDIR = ./includes/

LIB = libft.a

LIBDIR = ./libft/

all: $(NAME)
	@echo "\e[31mDEPENDENCY TO EXEC TO BE REMOVED\e[0m"

$(NAME): $(INCLS) $(SRCS)
#
	@rm -f auteur
	@echo hehlinge > auteur
	@/bin/echo creating $(LIBDIR)$(LIB)
	@make -j --no-print-directory -C $(LIBDIR)
	@/bin/echo compiling source files
	@mkdir -p objs
	@make -j --no-print-directory objects
	@$(CC) $(CFLAGS) -I $(INCLDIR) -o $@ $(OBJS) $(LIBDIR)/$(LIB)
#	@clear

objects: $(OBJS)

$(OBJDIR)%.o: $(SRCDIR)%.c
#
	@$(CC) $(CFLAGS) -I $(INCLDIR) -o $@ -c $<

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
