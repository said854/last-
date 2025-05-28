/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:21:24 by hakader           #+#    #+#             */
/*   Updated: 2025/05/28 12:41:07 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	handle_semicolon_case(t_cmd **cmd_list, t_cmd **current_cmd)
{
	if (is_cmd_empty(*current_cmd))
	{
		print_error("near unexpected token `;'");
		return (0);
	}
	add_cmd_to_list(cmd_list, *current_cmd);
	return (1);
}

static void	handle_pipe_case(t_cmd **cmd_list, t_cmd **current_cmd,
		t_list *alloc_list)
{
	(*current_cmd)->has_pipe = 1;
	add_cmd_to_list(cmd_list, *current_cmd);
	*current_cmd = create_cmd(alloc_list);
}

static int	handle_token_case(t_token **current, t_cmd **cmd_list,
		t_cmd **current_cmd, t_list *alloc_list, t_shell *shell)
{
	t_token	*token;

	token = *current;
	if (token->type == PIPE)
	{
		handle_pipe_case(cmd_list, current_cmd, alloc_list);
	}
	else if (token->type == SEMICOLON)
	{
		if (!handle_semicolon_case(cmd_list, current_cmd))
			return (0);
		*current_cmd = create_cmd(alloc_list);
	}
	else
	{
		if (!handle_token_redirection_or_arg(current, *current_cmd, alloc_list, shell))
			return (0);
	}
	return (1);
}

t_cmd	*build_cmd_list(t_token *tokens, t_list *alloc_list, t_shell *shell)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	t_token	*current;

	cmd_list = NULL;
	current_cmd = create_cmd(alloc_list);
	current = tokens;
	while (current)
	{
		if (!handle_token_case(&current, &cmd_list, &current_cmd, alloc_list, shell))
			return (NULL);
		current = current->next;
	}
	if (!is_cmd_empty(current_cmd))
		add_cmd_to_list(&cmd_list, current_cmd);
	return (cmd_list);
}
