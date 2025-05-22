/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:23:38 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/20 20:58:36 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"



int	is_empty(char *line)
{
	return (line[0] == '\0');
}
void	sigint_prompt_handlera(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	*line;
	t_list	*alloc_list = NULL;
	t_shell	*shell = ft_malloc(sizeof(t_shell), &alloc_list);
	if (!shell)
		return (1);
	ft_bzero(shell, sizeof(t_shell));
    shell->envp = envp;
	int i;

    i = 0;
	while (envp[i])
	{
		t_env *node = env_copy(envp[i], alloc_list);
		if (node)
			append_env(&shell->env, node);
		i++;
	}
	// mini_display();
	while (1)
	{
		signal(SIGINT, sigint_prompt_handler);
		line = readline(CYAN "minishell$ " RESET);
		signal(SIGINT, sigint_prompt_handlera);
		if (!line)
		{
			int status = shell->exit_status;
			free_all(&alloc_list); 
			exit(status);         
		}
		else if (!(is_empty(line)))
			add_history(line);
		shell->tokens = tokenize_line(shell, line, alloc_list);
		if (shell->tokens && check_syntax(shell))
		{
			shell->cmds = build_cmd_list(shell->tokens, alloc_list);
			if (shell->cmds)
			{
				// printf("here\n");
				// print_cmd_list(shell->cmds);
				execution_part(shell, &alloc_list);
			}
		}
		shell->tokens = NULL;
		shell->cmds = NULL;
		free(line);

	}
	return (0);
}
