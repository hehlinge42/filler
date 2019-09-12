/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:35:34 by hehlinge          #+#    #+#             */
/*   Updated: 2019/09/12 17:58:17 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_printf.h"
# include <string.h>
# define BUFF_SIZE 1

typedef struct		s_lst
{
	void			*content;
	size_t			content_size;
	struct s_lst	*next;
	struct s_lst	*last;
}					t_lst;

typedef struct		s_gc_list
{
	unsigned		len;
	t_lst			*first;
	t_lst			*last;
}					t_gc_list;

typedef struct		s_gnl
{
	int				fd;
	char			buf[BUFF_SIZE + 1];
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(const int fd, char **line);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
size_t				ft_strnlen(const char *s, size_t maxlen);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_itoa(int n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
int					ft_strchr_pos(char *s, int c);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *haystack, const char *needle,
		size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
t_lst				*ft_lstmap(t_lst *lst, t_lst *(*f)(t_lst *elem));
t_lst				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstpop(t_lst **begin, void **match, int opt);
void				ft_bzero(void *s, size_t n);
void				ft_lstadd(t_lst **alst, t_lst *new);
void				ft_lstadd_back(t_lst **alst, t_lst *new);
t_lst				*ft_lstadd_new(t_lst **alst, void *content, int size);
void				ft_lstclr(t_lst **begin_lst);
void				ft_lstdel(t_lst **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_lst **alst, void (*del)(void*, size_t));
void				ft_lstiter(t_lst *lst, void (*f)(t_lst *elem));
int					ft_lstprint(t_lst *begin_list, int opt);
void				ft_memdel(void **ap);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_strclr(char *s);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				*ft_memalloc(size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *restrict dst, const void *restrict src,
		int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*easymalloc(int size);
void				ft_free(void **ptr);
void				begin(void) __attribute__((constructor));
void				end(void) __attribute__((destructor));
int					ft_abs(int a);
int					ft_max(int a, int b);
int					ft_printf(const char *format, ...);

#endif
