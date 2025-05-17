/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:47:09 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/17 17:43:01 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_shell *shell_context = NULL;

void	sigint_prompt_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (shell_context)
		shell_context->exit_status = 130;
}

void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (shell_context)
		shell_context->exit_status = 130;
}

void	set_prompt_signals(t_shell *shell)
{
	shell_context = shell;
	signal(SIGINT, sigint_prompt_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_heredoc_signals(t_shell *shell)
{
	shell_context = shell;
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
