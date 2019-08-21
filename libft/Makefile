# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/10 16:35:23 by hehlinge          #+#    #+#              #
#    Updated: 2019/08/21 18:40:09 by sikpenou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = libft.a

FLAGS = -Wall -Wextra -Werror -g3

LIBFTPRINTF = libftprintf.a

LIBFTPRINTFDIR = ./ft_printf/

INC_DIR = includes

SRC_DIR = srcs

OBJ_DIR = obj

OBJS_LIB = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

LIBSRCS = $(addprefix $(SRC_DIR)/,$(SRCS))

SRCS = 	ft_atoi.c \
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
		ft_print_list.c \
		ft_malloc.c \
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
		get_next_line.c


all: $(NAME)

$(NAME): $(OBJS_LIB)
	@make -j --no-print-directory -C $(LIBFTPRINTFDIR)
	@mkdir -p $(OBJ_DIR)
	@echo "creating libft.a"
	@ar rc $(NAME) $(OBJS_LIB)
	@echo "indexing libft.a"
	@ranlib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
