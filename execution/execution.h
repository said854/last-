/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:02 by hakader           #+#    #+#             */
/*   Updated: 2025/05/19 21:19:32 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "../minishell.h"

/* ======================== EXECUTION CORE ======================== */

void	execution_part(t_shell *shell, t_list **alloc_list);
void	mini_display(void);
void	print_arr(char **arr);
void	print_this(t_env **env_list, char *sch);

/* ======================== BUILTIN COMMANDS ======================== */

int		execute_cd(t_cmd *cmd, t_env **env, t_list *alloc_list);
int		execute_pwd(t_cmd *cmd);
int		execute_echo(t_cmd *cmd);
int		execute_env(t_cmd *cmd, t_env *envp);
void	execute_exit(t_shell *shell, t_list *alloc_list);
int		execute_export(t_shell **shell, t_list *alloc_list);
int		excute_unset(t_shell **shell, t_list *alloc);
int		exec_builtin(t_shell **shell, t_list *alloc_list);

/* ======================== BUILTIN HELPERS ======================== */

int		check_exp(t_shell *shell);
int		is_new_line(char *arg);
void	env_path(t_env **env_list, t_cmd *cmd);
void	update_env(t_env **env, char *key, char *val, t_list *alloc);
void	ft_envadd_back(t_env **env, char *key, char *val, t_list *alloc);
t_env	*ft_new_env(char *key, char *val, t_list *alloc_list);

/* ======================== PATH RESOLUTION ======================== */

char	**get_paths(t_shell **shell, t_list *alloc_list);
char	*check_cmd(char **paths, char *cmd, t_list *alloc_list);
int		count_args(char **args);

/* ======================== STRING UTILS ======================== */

char	**ft_split(char const *s, char c, t_list *alloc_list);
int		ft_strcmp(const char *str1, const char *str2);

/* ======================== MEMORY ======================== */

void	free_all(t_list **alloc_list);

/* ======================== REDIRECTIONS ======================== */


int		read_heredoc(t_cmd *cmd, t_shell *shell, t_list *alloc_list);
/* ======================== ECHO HELPERS ======================== */

int		open_and_write(t_cmd *cmd, int flag, int index);

/* ======================== PIPES ======================== */

void	pipex(t_shell **shell, t_list *alloc_list);

int		is_builtin_name(const char *name);
void	update_exit_status(t_shell *shell, pid_t pid);
void	set_cmd_not_found(t_shell *shell, char *cmd);
int		open_all_infiles(char **infiles);
int		open_all_outfiles(char **outfiles, int *append_flags);
int		io_error(t_shell *shell);
int		if_builtin(t_shell *shell, t_list *alloc_list);
int		is_valid_key(char *s);
void	non_valide(t_shell **shell, char *identifier);
char	*get_key(char *arg, t_list *alloc_list);
char	*get_value(char *arg, t_list *alloc_list);

#endif
