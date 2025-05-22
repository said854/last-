/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:57:06 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/19 21:12:55 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* LIBRARYS */

# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_INVALID_ARGS 2

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_split_data
{
	char			**ptr;
	int				count;
	t_list			*alloc_list;
}					t_split_data;

/* PART 1 */

long				ft_atoi(const char *str, t_list *alloc_list);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size, t_list *alloc_list);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(char const *s1, char const *s2,
						t_list *alloc_list);
size_t				ft_strlen(const char *s);
int					ft_isspace(int c);
int					is_quote(char *str);
int					is_operator(char c);
void				ft_putstr_fdput_error(char *msg);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char 				*ft_strndup(const char *s, size_t n, t_list *alloc_list);

/* PART 2 */

char				*ft_substr(char const *s, unsigned int start, size_t len,
						t_list *alloc_list);
char				*ft_strdup(const char *str, t_list *alloc_list);
void				ft_putendl_fd(char *s, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char const *s, char c, t_list *alloc);
char				*ft_itoa(int n, t_list *alloc_list);

/* BONUS PART */

void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);

void				*ft_malloc(size_t size, t_list **alloc_list);
void				free_all(t_list **alloc_list);
void				put_error(char *msg);
#endif
