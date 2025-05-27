/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:23:38 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/27 21:31:21 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


static void	setup_shell_env(t_shell *shell, char **envp, t_list **alloc_list)
{
	int		i;
	t_env	*node;

	i = 0;
	shell->envp = envp;
	while (envp[i])
	{
		node = env_copy(envp[i], *alloc_list);
		if (node)
			append_env(&shell->env, node);
		i++;
	}
}

static void	handle_exit(char *line, t_shell *shell, t_list **alloc_list)
{
	int	status;

	if (!line)
	{
		status = shell->exit_status;
		free_all(alloc_list);
		exit(status);
	}
}

static void	process_line(char *line, t_shell *shell, t_list **alloc_list)
{
	if (!(line[0] == '\0'))
		add_history(line);
	shell->tokens = tokenize_line(shell, line, *alloc_list);
	if (shell->tokens && check_syntax(shell))
	{
		shell->cmds = build_cmd_list(shell->tokens, *alloc_list, shell);
		if (shell->cmds)
			execution_part(shell, alloc_list);
	}
	shell->tokens = NULL;
	shell->cmds = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	t_list	*alloc_list;
	char	*line;

	(void)ac;
	(void)av;
	alloc_list = NULL;
	shell = ft_malloc(sizeof(t_shell), &alloc_list);
	if (!shell)
		return (1);
	ft_bzero(shell, sizeof(t_shell));
	setup_shell_env(shell, envp, &alloc_list);
	while (1)
	{
		set_prompt_signals(shell);
		line = readline(CYAN "minishell$ " RESET);
		signal(SIGINT, sigint_prompt_handlera);
		handle_exit(line, shell, &alloc_list);
		process_line(line, shell, &alloc_list);
		free(line);
	}
	return (0);
}
