# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/10 16:10:57 by hehlinge          #+#    #+#              #
#    Updated: 2019/06/11 19:09:15 by hehlinge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

LIBFT = libft

SRC_DIR = srcs

OBJ_DIR = objs

INC = includes

SOURCES = ft_char.c         ft_pointer.c      ft_uint_tools.c	ft_float_anormal.c\
		  ft_display_int.c  ft_float.c        ft_parsing.c      ft_printf.c\
		  ft_int.c          ft_parsing_type.c ft_string.c		ft_percent.c\
		  ft_bits.c			ft_uint.c		  ft_float_calc.c	ft_float_strct.c\
		  ft_float_strct_round.c

SRCS = $(addprefix $(SRC_DIR)/,$(SOURCES))

OBJS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -I $(INC) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

debug: all
	$(CC) -g3 $(CFLAGS) -I includes -o main.o -c main.c
	$(CC) -g3 $(CFLAGS) -o test_printf main.o libftprintf.a libft/libft.a
