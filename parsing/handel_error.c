/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:46:03 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/17 22:35:39 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_redirection(t_token_type type)
{
	return (type == REDIR_OUT || type == REDIR_IN || type == APPEND
		|| type == HEREDOC);
}

int	print_error(char *message)
{
	ft_putstr_fd("minishell : syntax error ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_SUCCESS);
}

int	return_syntaxx(t_shell *shell, int len)
{
	if (len == -1)
		print_error("near unexpected token `|`");
	else if (len == -2)
		print_error("missing filename after redirection");
	else if (len == -3)
		print_error("unexpected end of input after `|`");
	shell->exit_status = 2;
	return (0);
}

int	check_syntax(t_shell *shell)
{
	t_token	*current;
	t_token	*prev;

	current = shell->tokens;
	prev = NULL;
	if (!current)
		return (0);
	if (current->type == PIPE)
		return (return_syntaxx(shell, -1));
	while (current)
	{
		if (prev && prev->type == PIPE && current->type == PIPE)
			return (return_syntaxx(shell, -1));
		if (is_redirection(current->type))
		{
			if (!current->next || current->next->type != WORD)
				return (return_syntaxx(shell, -2));
		}
		prev = current;
		current = current->next;
	}
	if (prev && prev->type == PIPE)
		return (return_syntaxx(shell, -3));
	return (EXIT_FAILURE);
}
