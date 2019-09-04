# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 21:32:05 by sikpenou          #+#    #+#              #
#    Updated: 2019/09/04 16:56:42 by sikpenou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

NAME = resources/players/hehlinge.filler
#NAME = hehlinge.filler

SRCS = $(addprefix $(SRCDIR), $(SRCFILES))

SRCFILES =	main.c				\
			parser.c			\
			points.c			\
			debug.c				\
			algo.c

SRCDIR = ./srcs/

OBJS = $(addprefix $(OBJDIR), $(OBJFILES))

OBJFILES = $(SRCFILES:.c=.o)

OBJDIR = objs/

INCLS = $(INCLDIR)*.h

INCLDIR = includes/

LIB = $(addprefix $(LIBDIR), libft.a)

LIBINCLS =  $(LIBDIR)$(INCLDIR)

LIBDIR = libft/

all: $(NAME)

$(NAME): $(INCLS) $(SRCS) $(LIB)
	@rm -f auteur
	@echo hehlinge > auteur
	@mkdir -p objs
	@make -j --no-print-directory objects
	@$(CC) $(CFLAGS) -I $(INCLDIR) -o $@ $(OBJS) $(LIB)

$(LIB):
	@make -j --no-print-directory -C $(LIBDIR)

objects: $(OBJS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -I $(INCLDIR) -I $(LIBINCLS) -o $@ -c $<

clean: FORCE
	@rm -f $(OBJS)
	@make clean -j --no-print-directory -C $(LIBDIR)
	@echo "rm -f .o files"
	@rm -f $(OBJS)

fclean: clean
	@rm -f a.out
	@rm -f test
	rm -f $(LIB)
	rm -f $(NAME)

re: FORCE
	@make -j --no-print-directory fclean
	@make -j --no-print-directory all

FORCE:
