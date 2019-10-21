# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 21:32:05 by sikpenou          #+#    #+#              #
#    Updated: 2019/10/21 13:33:06 by sikpenou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = hehlinge.filler

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

SRC_FILES =	main.c				\
			parser.c			\
			points.c			\
			algo.c

SRC_DIR = ./srcs/

OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)

OBJ_DIR = objs/

INCLS = $(INC_DIR)filler.h

INC_DIR = includes/

LIB = $(addprefix $(LIB_DIR), libft.a)

LIB_INCLS = $(LIB_DIR)$(INC_DIR)

LIB_DIR = libft/

COLOR = color/color

all: $(NAME)

$(NAME): $(INCLS) $(LIB_INCLS) $(SRCS) $(LIB) $(COLOR)
	@/bin/echo "make $(notdir $(NAME))"
	@rm -f auteur
	@echo hehlinge > auteur
	@mkdir -p objs
	@make -j --no-print-directory objects
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ $(OBJS) $(LIB)
	@cp $(NAME) resources/players

$(LIB): FORCE
	@make -j --no-print-directory -C $(LIB_DIR)

$(COLOR): FORCE
	@make -j --no-print-directory -C color/	

objects: $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLS)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIB_INCLS) -o $@ -c $<

clean: FORCE
	@/bin/echo "make clean $(notdir $(NAME))"
	@rm -rf $(OBJ_DIR)
	@make clean -j --no-print-directory -C $(LIB_DIR)
	@make clean -j --no-print-directory -C color/

fclean: clean
	@/bin/echo "make fclean $(notdir $(NAME))"
	@make fclean -j --no-print-directory -C $(LIB_DIR)
	@make fclean -j --no-print-directory -C color/
	@rm -f resources/color
	@rm -f resources/debug.txt
	@rm -f $(NAME)


re: FORCE
	@/bin/echo "make re $(notdir $(NAME))"
	@make -j --no-print-directory fclean
	@make -j --no-print-directory all

FORCE:
