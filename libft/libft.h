/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:24:42 by prynty            #+#    #+#             */
/*   Updated: 2024/12/22 13:40:25 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# define UP_HEX_BASE "0123456789ABCDEF"
# define LOW_HEX_BASE "0123456789abcdef"

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//character functions
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(char *str);
int		ft_toupper(int c);
int		ft_tolower(int c);

//memory functions
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_free_array(char ***str);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *str, int c, size_t len);

//string functions
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *str, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *src);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dest, const char *src, size_t destsize);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//type converter functions
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

//file descriptor functions
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//list manipulation functions
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//ft_printf
int		ft_printf(const char *str, ...);
int		ft_print_char(char c);
int		ft_print_str(const char *str);
int		ft_print_nbr(int n);
int		ft_print_nbr_unsigned(unsigned int n);
int		ft_print_ptr(unsigned long long ptr);
int		ft_print_hex(unsigned long long n, const char format);

//ft_printf_fd
int		ft_printf_fd(int fd, const char *str, ...);
int		ft_print_char_fd(int fd, char c);
int		ft_print_str_fd(int fd, const char *str);
int		ft_print_nbr_fd(int fd, int n);
int		ft_print_nbr_unsigned_fd(int fd, unsigned int n);
int		ft_print_ptr_fd(int fd, unsigned long long ptr);
int		ft_print_hex_fd(int fd, unsigned long long n, const char format);

//gnl
char	*get_next_line(int fd);
size_t	gnl_strlen(char *str);
char	*gnl_strchr(char *str, char chr);
char	*gnl_strjoin(char *dst, char *src, size_t len);
void	gnl_copy(char *dst, char *src);
void	gnl_bzero(char *buf, size_t size);

#endif
