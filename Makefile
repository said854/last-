NAME = minishell
CC = cc
# CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC1 = parsing/array_helpers.c parsing/env_copy.c parsing/get_token_length.c \
       parsing/handle_token_redirection.c parsing/parce_cmd.c   parsing/parcing.c \
       parsing/signals.c parsing/token_utils.c parsing/build_cmd_list.c \
       parsing/expand.c  parsing/handel_error.c parsing/minishell.c \
       parsing/parce_dollar.c parsing/token_helpers.c

SRC2 = execution/tools_1.c execution/tools_2.c \
       execution/execution.c execution/in_out.c execution/pipe.c \
       execution/exit_status.c execution/heredoc.c execution/errors.c \
       execution/builtin/built_in.c execution/builtin/ft_echo.c \
       execution/builtin/ft_exit.c execution/builtin/ft_export.c \
       execution/builtin/ft_export_helpers.c execution/builtin/ft_unset.c \
       execution/builtin/ft_cd.c execution/builtin/ft_env.c \
       execution/builtin/ft_pwd.c execution/test.c \
       execution/builtin/ft_export_helpers2.c execution/check_options.c \
       execution/print.c execution/testddd.c

EXTRA = libft/ft_malloc.c libft/ft_strcmp.c

SRC = $(SRC1) $(SRC2) $(EXTRA)

OBJ = $(SRC:.c=.o)

LIBFT_SRC = libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c \
            libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_strchr.c \
            libft/ft_strdup.c libft/ft_strlen.c libft/ft_substr.c \
            libft/ft_strjoin.c libft/ft_split.c libft/ft_itoa.c \
            libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_isspace.c \
            libft/ft_lstadd_back_bonus.c libft/ft_lstclear_bonus.c \
            libft/ft_lstdelone_bonus.c libft/ft_lstlast_bonus.c \
            libft/ft_lstnew_bonus.c libft/ft_atoi.c libft/ft_errors.c

LIBFT_FILES = $(LIBFT_SRC) libft/libft.h

# Color output
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RESET = \033[0m

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
	@$(MAKE) -C $(LIBFT_DIR) --silent

clean:
	@rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --silent
	@echo "$(CYAN)🧹 Object files cleaned$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@echo "$(CYAN)🧼 Full cleanup complete$(RESET)"

re: fclean all

.PHONY: all clean fclean re start_build end_build
