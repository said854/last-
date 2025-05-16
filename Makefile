
NAME = minishell
CC = cc
# CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = parsing/minishell.c parsing/parcing.c parsing/parce_dollar.c parsing/handel_error.c \
      parsing/parce_cmd.c parsing/env_copy.c parsing/free_all.c parsing/print_lists.c \
      parsing/signals.c execution/tools_1.c execution/tools_2.c execution/execution.c \
      execution/in_out.c execution/pipe.c execution/builtin/built_in.c \
      execution/builtin/unset.c execution/builtin/expuns_utils1.c \
      execution/builtin/expuns_utils2.c execution/builtin/echo.c \
      execution/builtin/tools1.c execution/builtin/export.c execution/builtin/test.c \
      libft/ft_malloc.c execution/exit_status.c execution/heredoc.c

OBJ = $(SRC:.c=.o)

LIBFT_SRC = libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c \
            libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_strchr.c \
            libft/ft_strdup.c libft/ft_strlen.c libft/ft_substr.c \
            libft/ft_strjoin.c libft/ft_split.c libft/ft_itoa.c \
            libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_isspace.c \
            libft/ft_lstadd_back_bonus.c libft/ft_lstclear_bonus.c \
            libft/ft_lstdelone_bonus.c libft/ft_lstlast_bonus.c \
            libft/ft_lstnew_bonus.c libft/ft_atoi.c libft/put_error.c

LIBFT_FILES = $(LIBFT_SRC) libft/libft.h

# Colors for pretty output
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RESET = \033[0m

# Default target
all: start_build $(LIBFT) $(NAME) end_build

start_build:
	@clear
	@echo "$(CYAN)🚀 Starting Minishell Build...$(RESET)"

end_build:
	@echo "$(GREEN)✅ Minishell built successfully$(RESET)"

$(NAME): $(OBJ)
	@echo "$(BLUE)🔧 Archiving object files into Minishell...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c libft/libft.h parsing/parsing.h execution/execution.h minishell.h
	@echo "$(YELLOW)⚙️  Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_FILES)
	@echo "$(YELLOW)📦 Rebuilding Libft...$(RESET)"
	@echo "$(YELLOW)✊ Building minishell...$(RESET)"
	@$(MAKE) -C libft --silent

clean:
	@rm -rf $(OBJ)
	@$(MAKE) -C libft clean --silent
	@echo "$(CYAN)🧹 Object files cleaned$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean --silent
	@echo "$(CYAN)🧼 Full cleanup complete$(RESET)"

re: fclean all

.PHONY: all clean fclean re start_build end_build
