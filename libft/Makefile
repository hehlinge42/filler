# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 21:32:05 by hehlinge          #+#    #+#              #
#    Updated: 2019/10/09 21:07:36 by hehlinge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRCS = $(addprefix $(SRCDIR), $(SRCFILES))

SRCFILES = \
			filler_gnl.c \
			ft_abs.c \
			ft_atoi.c \
			ft_atoi_base.c \
			ft_bzero.c \
			ft_check_base.c \
			ft_convert_base.c \
			ft_fili.c \
			ft_free_ptr.c \
			ft_free_tab.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_itoa.c \
			ft_itoa_base.c \
			ft_lst_at.c \
			ft_lst_find.c \
			ft_lst_last.c \
			ft_lst_merge.c \
			ft_lst_size.c \
			ft_lst_sort.c \
			ft_lstadd.c \
			ft_lstadd_back.c \
			ft_lstadd_new.c \
			ft_lstclr.c \
			ft_lstcycle.c \
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
			ft_memchr.c \
			ft_memchr_pos.c \
			ft_memchrset.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memcset.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_min.c \
			ft_pow.c \
			ft_print_words_tables.c \
			ft_printf.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_putstr_fd_ret.c \
			ft_putstr_ret.c \
			ft_realloc.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strchr_pos.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strjoin_free.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strrev.c \
			ft_strsplit.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_swap.c \
			ft_swapstr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_ulltoa.c \
			calc_floats_pf.c \
			core_pf.c \
			floats_pf.c \
			num_funcs_pf.c \
			padding_pf.c \
			round_floats_pf.c \
			str_calc_pf.c \
			support_pf.c \
			text_funcs_pf.c \
			val_neg_4k_pf.c \
			val_neg_8k_pf.c \
			val_pos_pf.c

SRCDIR = srcs/

OBJS = $(addprefix $(OBJDIR), $(OBJFILES))

OBJFILES = $(SRCFILES:.c=.o)

OBJDIR = objs/

INCLS = $(INCLDIR)libft.h

INCLDIR = includes/

all: $(NAME)

$(NAME): $(INCLS) $(SRCS)
	@/bin/echo make $(NAME)
	@rm -f auteur
	@echo hehlinge > auteur
	@mkdir -p $(OBJDIR)
	@make -j --no-print-directory objects
	@ar src $(NAME) $(OBJS)

objects: $(OBJS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -I $(INCLDIR) -o $@ -c $<

clean: FORCE
	@rm -rf $(OBJDIR)
	@echo "rm -f .o files"

fclean: clean
	@rm -f a.out
	@rm -f test
	rm -f $(NAME)
	rm -f ft_printf

re: FORCE
	@make -j --no-print-directory fclean
	@make -j --no-print-directory all

FORCE:
