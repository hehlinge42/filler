/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:00:02 by hehlinge          #+#    #+#             */
/*   Updated: 2019/06/12 13:19:17 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/includes/libft.h"
# include <stdarg.h>

# define FD 1
# define BUF_SIZE 1024
# define BUF_FLOAT 16384

# define FLAG_PLUS 0
# define FLAG_MINUS 1
# define FLAG_SPACE 2
# define FLAG_ZERO 3
# define FLAG_HASH 4

# define LENGTH_HH 1
# define LENGTH_H 2
# define LENGTH_L 3
# define LENGTH_LL 4
# define LENGTH_BIGL 5

# define CONVERT_C 1
# define CONVERT_D 2
# define CONVERT_U 3
# define CONVERT_X 4
# define CONVERT_XX 5
# define CONVERT_O 6
# define CONVERT_F 7
# define CONVERT_S 8
# define CONVERT_P 9
# define CONVERT_B 10
# define CONVERT_PE 11
# define CONVERT_FF 12
# define CONVERT_FAKE 13
# define CONVERT_BB 14

# define MY_NAN 1
# define MINUS_INF 2
# define PLUS_INF 3

typedef unsigned long long	ull;

typedef struct		s_printf
{
	char	flag[5];
	int		width;
	int		precision;
	int		length;
	int		convert;
	char	fake_c;
}					t_printf;

typedef struct		s_buffer
{
	char				buf[BUF_SIZE + 1];
	unsigned long long	index;
	unsigned long long	count_total_char;
}					t_buffer;

typedef struct		s_float
{
	long double			nb;
	int					sign;
	int					exponent;
	unsigned long long	float_mantissa;
	unsigned long long	floor_mantissa;
	int					shift;
	int					shift_float;
	int					float_size;
	int					anormal;
	char				tab_res[3][BUF_FLOAT + 1];
}					t_float;

int					ft_parse(char **str, t_printf *var);
int					ft_printf(const char *format, ...);
int					ft_is_convert_type(t_printf *var, char *c);
void				ft_putnbr_ullbase(unsigned long long nbr, int base_size, char letter_case, t_buffer *buffer);
int					ft_ucount_chars(unsigned long long ull, int base_size);
int					ft_find_base(t_printf *strct, va_list va);
void				ft_print_width(t_printf *strct, t_buffer *buffer, int count);
int					ft_bits(t_printf *strct, t_buffer *buffer, va_list va);
int					ft_char(t_printf *strct, t_buffer *buffer, va_list va);
int					ft_int(t_printf *strct, t_buffer *buffer, va_list va);
int					ft_uint(t_printf *strct, t_buffer *buffer, va_list va);
int					ft_float(t_printf *strct, t_buffer *buffer, va_list va);
int					ft_pointer(t_printf *strct, t_buffer *buffer, va_list va);
int					ft_string(t_printf *strct, t_buffer *buffer, va_list va);
int					ft_percent(t_printf *strct, t_buffer *buffer, va_list va);
void				ft_display_flag_plus(t_printf *strct, t_buffer *buffer);
void				ft_display_precision(t_printf *strct, int count, t_buffer *buffer, long long nb);
char				ft_find_letter(t_printf *strct);
void				ft_write_buf(char *str, t_buffer *buffer, unsigned long long size);
void				ft_fill_float_strct(t_float *float_nb, t_printf *strct, va_list va);
long double			ft_return_ld(t_printf *strct, va_list va);
void				ft_divide_nb(char to_divide[BUF_FLOAT + 1]);
void				ft_double_nb(char to_double[BUF_FLOAT + 1]);
void				ft_sum(char part1[BUF_FLOAT + 1], char part2[BUF_FLOAT + 1], int opt);
void				ft_round(t_float *float_nb, int precision);
void				ft_memmove_float(char nb[BUF_FLOAT + 1], int float_size, int shift);
void				ft_display_hash(t_printf *strct, t_buffer *buffer);
void				ft_anormal(t_float *float_nb);
int					ft_manage_anormal(t_float *float_nb, t_printf *strct, t_buffer *buffer);
int					ft_float_size(unsigned long long mantissa);

#endif
