/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:33:14 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/15 13:39:05 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_buf
{
	char	*buffer;
	int		end_file;
}	t_buf;

// characters
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

int		ft_toupper(int c);
int		ft_tolower(int c);

// string
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *big, const char *little);
char	*ft_strnstr(const char *big, const char *little, int len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, int len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free_1st_p(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
int		ft_strcpy(char *dst, const char *src);
int		ft_strlcpy(char *dst, const char *src, int size);
int		ft_strcat(char *dst, const char *src);
int		ft_strlcat(char *dst, const char *src, int size);

// memory
void	*ft_memset(void *s, int c, int n);
void	*ft_memcpy(void *dest, const void *src, int n);
void	*ft_memmove(void *dest, const void *src, int n);
void	*ft_memchr(const void *s, int c, int n);
int		ft_memcmp(const void *s1, const void *s2, int n);
void	ft_bzero(void *s, int n);

// number
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

// alloc
void	*ft_calloc(int nmemb, int size);

// print
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr_base_fd(int n, int fd, char *base);

// chain list
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// get next line
char	*get_next_line(int fd);

// printf
void	ft_print_char(char c, int *nb_char_print);
void	ft_print_string(char *str, int *nb_char_print);
void	ft_print_int(int nb, int *nb_char_print);
void	print_uint(unsigned int nb);
void	ft_print_uint(unsigned int nb, int *nb_char_print);
void	print_hex(unsigned int nb, char *base);
char	*itoa_hex(size_t nb, char *base, char *str);
void	ft_print_lowerhex(unsigned int nb, int *nb_char_print);
void	ft_print_upperhex(unsigned int nb, int *nb_char_print);
void	ft_print_pointer(void *p, int *nb_char_print);
void	print_param(char pc, char c, va_list args, int *nb_char_print);
int		ft_printf(const char *str, ...);
#endif
