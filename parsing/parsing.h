/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:20:48 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/29 15:41:36 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "../minishell.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

t_token			*tokenize_line(t_shell *shell, char *line, t_list *alloc_list);
char			*expand_token_value(char *value, t_shell *shell,
					t_list *alloc_list);
int				check_syntax(t_shell *shell);
t_cmd			*build_cmd_list(t_token *tokens, t_list *alloc_list, t_shell *shell);
t_env			*env_copy(char *content, t_list *alloc_list);
int				ft_isspace(int c);
t_token_type	get_token_type(char *str);
t_token			*create_token(char *str, t_token_type type, t_list *alloc_list);
void			append_token(t_token **head, t_token *new);
t_token			*return_syntax(t_shell *shell, int len);
int				should_expand_dollar(char *str);
t_token			*split_expanded(char *str, t_list *alloc_list);
char			*remove_quotes(const char *str, t_list *alloc_list);
t_heredoc_tmp	*alloc_array(t_heredoc_tmp *old, int new_count,
					t_list *alloc_list);
int				is_cmd_empty(t_cmd *cmd);
int				get_token_length(char *line, int i);
int				is_token_end(char c, int in_squote, int in_dquote);
int				handle_quotes(char *line, int *i, int *squote, int *dquote);
int				handle_backslash(char *line, int *i);
int				check_semicolon(char *line, int i);
int				check_operator(char *line, int i);
t_cmd			*create_cmd(t_list *alloc_list);
void			add_arg_to_cmd(t_cmd *cmd, char *arg, t_list *alloc_list);
void			add_cmd_to_list(t_cmd **head, t_cmd *new_cmd);
char			**append_str_array(char **arr, char *new_str,
					t_list *alloc_list);
int				get_int_array_length(int *arr);
int				*append_int_array(int *arr, int value, t_list *alloc_list);
int				handle_token_redirection_or_arg(t_token **current, t_cmd *cmd,
					t_list *alloc_list, t_shell *shell);

void			append_env(t_env **head, t_env *new_node);

void			set_prompt_signals(t_shell *shell);
void			sigint_prompt_handler(int sig);
void			set_child_signals(void);
int				print_error(char *message);
void			sigint_prompt_handlera(int sig);

#endif
