# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/10 16:35:23 by hehlinge          #+#    #+#              #
#    Updated: 2019/09/12 16:59:41 by sikpenou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libft.a

FLAGS = -Wall -Wextra -Werror -g3

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

SRC_DIR = srcs/

SRC_FILES = 	ft_abs.c \
				ft_atoi.c \
				ft_bzero.c \
				ft_itoa.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_lstadd.c \
				ft_lstadd_back.c \
				ft_lstadd_new.c \
				ft_lstclr.c \
				ft_lstdel.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstpop.c \
				ft_lstprint.c \
				ft_malloc.c \
				ft_max.c \
				ft_memalloc.c \
				ft_memccpy.c \
				ft_memcpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memdel.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putendl.c \
				ft_putnbr.c \
				ft_putnbr_fd.c \
				ft_putstr.c \
				ft_putstr_fd.c \
				ft_strdel.c \
				ft_strmapi.c \
				ft_strsplit.c \
				ft_strdup.c \
				ft_strncat.c \
				ft_strstr.c \
				ft_strequ.c \
				ft_strncmp.c \
				ft_strsub.c \
				ft_striter.c \
				ft_strncpy.c \
				ft_strtrim.c \
				ft_strcat.c \
				ft_striteri.c \
				ft_strnequ.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strchr_pos.c \
				ft_strjoin.c \
				ft_strnew.c \
				ft_strclr.c \
				ft_strlcat.c \
				ft_strnlen.c \
				ft_strcmp.c \
				ft_strlen.c \
				ft_strnstr.c \
				ft_strcpy.c \
				ft_strmap.c \
				ft_strrchr.c \
				ft_toupper.c \
				get_next_line.c \
				ft_bits.c \
				ft_char.c \
				ft_display_int.c \
				ft_float.c \
				ft_float_anormal.c \
				ft_float_calc.c \
				ft_float_strct.c \
				ft_float_strct_round.c \
				ft_int.c \
				ft_parsing.c \
				ft_parsing_type.c \
				ft_percent.c \
				ft_pointer.c \
				ft_printf.c \
				ft_string.c \
				ft_uint.c \
				ft_uint_tools.c

INCLS = $(INC_DIR)*.h

INC_DIR = includes/

OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)

OBJ_DIR = objs/

all: $(NAME)

$(NAME): $(INCLS) $(SRCS)
	@/bin/echo "make $(notdir $(NAME))"
	@mkdir -p $(OBJ_DIR)
	@make -j --no-print-directory objects
	@ar sucr $(NAME) $(OBJS)


objects: $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLS)
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

clean:
	@/bin/echo "make clean $(notdir $(NAME))"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@/bin/echo "make fclean $(notdir $(NAME))"
	@rm -f $(NAME)

re: fclean all
	@/bin/echo "make re $(notdir $(NAME))"

.PHONY: all clean fclean re
