# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/10 16:35:23 by hehlinge          #+#    #+#              #
#    Updated: 2019/05/10 16:40:01 by hehlinge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

INC = libft.h

SRC_DIR = srcs

OBJ_DIR = obj

OBJS_LIB = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

LIBSRCS = $(addprefix $(SRC_DIR)/,$(SRCS))

SRCS = ft_atoi.c       ft_lstclr.c     ft_memcmp.c     ft_putnbr.c     ft_strdel.c     ft_strmapi.c    ft_strsplit.c\
	   ft_bzero.c      ft_lstdel.c     ft_memcpy.c     ft_putnbr_fd.c  ft_strdup.c     ft_strncat.c    ft_strstr.c\
	   ft_isalnum.c    ft_lstdelone.c  ft_memdel.c     ft_putstr.c     ft_strequ.c     ft_strncmp.c    ft_strsub.c\
	   ft_isalpha.c    ft_lstiter.c    ft_memmove.c    ft_putstr_fd.c  ft_striter.c    ft_strncpy.c    ft_strtrim.c\
	   ft_isascii.c    ft_lstmap.c     ft_memset.c     ft_strcat.c     ft_striteri.c   ft_strnequ.c    ft_tolower.c\
	   ft_isdigit.c    ft_lstnew.c     ft_putchar.c    ft_strchr.c     ft_strjoin.c    ft_strnew.c     ft_toupper.c\
	   ft_isprint.c    ft_memalloc.c   ft_putchar_fd.c ft_strclr.c     ft_strlcat.c    ft_strnlen.c    get_next_line.c\
	   ft_itoa.c       ft_memccpy.c    ft_putendl.c    ft_strcmp.c     ft_strlen.c     ft_strnstr.c\
	   ft_lstadd.c     ft_memchr.c     ft_putendl_fd.c ft_strcpy.c     ft_strmap.c     ft_strrchr.c

all: $(NAME)

$(NAME): $(OBJS_LIB)
	@mkdir -p $(OBJ_DIR)
	@ar rc $(NAME) $(OBJS_LIB)
	@ranlib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -I $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
