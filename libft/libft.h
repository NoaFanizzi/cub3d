/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:11:12 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/10/04 10:56:31 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

typedef enum e_bool
{
	true = 1,
	false = 0
}					t_bool;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstfirst(t_list *lst);
t_list				*ft_lstget_index(t_list *lst, size_t index);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstdup(const t_list *lst, void (*del)(void*));
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstswap(t_list *l1, t_list *l2);
int					ft_lstsize(t_list *lst);
int					ft_lstindex(t_list *lst, t_list *to_find);

int					ft_printf(const char *format, ...);

int					ft_strncmp(const char *s1, const char *s2, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_count_words(char const *str, int c);
int					ft_atoi(const char *nptr);
int					ft_abs(int n);
int					ft_toupper(int c);
int					ft_tolower(int c);

int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(const char *s, int fd);
int					ft_putendl_fd(char *s, int fd);
int					ft_putnbr_fd(long long int n, int fd);
int					ft_putnbr_base_fd(long long int n, char *base, int fd);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

//check if is alpha
t_bool				ft_isalpha(int c);
t_bool				ft_isdigit(int c);
t_bool				ft_isalnum(int c);
t_bool				ft_isprint(int c);
t_bool				ft_isascii(int c);
t_bool				ft_isspace(int c);
t_bool				ft_islower(int c);
t_bool				ft_isupper(int c);

long int			ft_atol(const char *nptr);
long int			ft_atol_base(const char *nptr, const char *base);
long int			ft_absl(long int nb);
long long int		ft_atoll(const char *nptr);

size_t				ft_strlen(const char *str);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);

void				ft_free(void *pnt);
void				ft_wipe(char **ptr);
void				ft_free_split(char **tab);
void				ft_bzero(void *s, size_t n);
void				ft_close_all(size_t nb, ...);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strdup(const char *s);
char				*ft_strndup(const char *s, int len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free(char *dest, const char *src);
char				*ft_strjoin_all(size_t	str_nb, ...);
char				*ft_strchr(const char *s, int c);
char				*ft_strrev(char *str);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strcrop(const char *str, int c);
char				*ft_itoa(int n);
char				*ft_llitoa(long long int n);
char				*get_next_line(int fd);
char				*ft_read_file(int fd);

char				**ft_split(const char *str, int c);
void 				remove_last_char(char *str);

#endif
