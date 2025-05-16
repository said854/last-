NAME    = libft.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar rcs
RM      = rm -f

SRCS =  ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
        ft_isdigit.c ft_strchr.c ft_strdup.c ft_strlen.c \
        ft_substr.c ft_strjoin.c ft_split.c ft_itoa.c \
        ft_putstr_fd.c ft_putendl_fd.c ft_isspace.c \
        ft_lstadd_back_bonus.c ft_lstclear_bonus.c \
        ft_lstdelone_bonus.c ft_lstlast_bonus.c \
        ft_lstnew_bonus.c ft_atoi.c ft_errors.c \
        ft_strncmp.c

HEADER = libft.h
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
