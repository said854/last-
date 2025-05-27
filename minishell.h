/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:56:19 by hakader           #+#    #+#             */
/*   Updated: 2025/05/23 10:51:33 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//EXIT_STATUS
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_INVALID_ARGS 2
extern int g_interrupted;


// extern volatile __sig_atomic_t g_signal_interrupted;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	APPEND,
	REDIR_OUT,
	HEREDOC,
	SEMICOLON
} t_token_type;

typedef struct s_heredoc_tmp
{
	char	*delim;
	int		expand;
}	t_heredoc_tmp;

typedef struct s_cmd
{
	char				**args;
	char				**infiles;
	char				**outfiles;
	int					*append_flags;
	int					has_pipe;
	t_heredoc_tmp		*heredocs;
	int					heredoc_count;
	char				*heredoc_delim;
	int					heredoc_expand;
	int					heredoc_fd;
	int					input_error;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_shell
{
	t_env	*env;
	t_token	*tokens;
	t_cmd	*cmds;
	char	**envp;
	int		exit_status;
}	t_shell;

// t_shell	shell;

# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft/libft.h"
# include "parsing/parsing.h"
# include "execution/execution.h"
# include <signal.h>
# include <sys/stat.h>
# include <errno.h>
# define RESET		"\x1b[0m"
# define BLACK		"\x1b[30m"
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\x1b[37m"



#endif
