/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:01:44 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/28 13:31:09 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_output_redir(t_cmd *cmd, int type, char *target, t_list *alloc_list)
{
	cmd->outfiles = append_str_array(cmd->outfiles, target, alloc_list);
	if (type == APPEND)
		cmd->append_flags = append_int_array(cmd->append_flags, 1, alloc_list);
	else
		cmd->append_flags = append_int_array(cmd->append_flags, 0, alloc_list);
	return (1);
}

int	handle_heredoc(
	t_cmd *cmd,
	char *target,
	char *raw_value,
	t_list *alloc_list
)
{
	char	*delim;
	int		expand;
	delim = remove_quotes(target, alloc_list);
	expand = is_quote(raw_value);
	cmd->heredocs = alloc_array(cmd->heredocs,
			cmd->heredoc_count + 1, alloc_list);
	cmd->heredocs[cmd->heredoc_count].delim = delim;
	cmd->heredocs[cmd->heredoc_count].expand = expand;
	cmd->heredoc_count++;
	if(cmd->heredoc_count >= 17)
		return(0);
	return (1);
}

int	handle_redirection(t_token **current, t_cmd *cmd, t_list *alloc_list, t_shell *shell)
{
	t_token	*token;
	char	*target;

	token = *current;
	if (!token->next || token->next->type != WORD)
		return (print_error("near unexpected token"));
	target = ft_strdup(token->next->value, alloc_list);
	target = remove_quotes(target, alloc_list);
	if (token->type == REDIR_IN)
	{
		cmd->infiles = append_str_array(cmd->infiles, target, alloc_list);
		cmd->rediriction = append_str_array(cmd->rediriction, target, alloc_list);
	}
	else if (token->type == REDIR_OUT || token->type == APPEND)
	{
		handle_output_redir(cmd, token->type, target, alloc_list);
		cmd->rediriction = append_str_array(cmd->rediriction, target, alloc_list);
	}
	else if (token->type == HEREDOC)
	{
		if (!handle_heredoc(cmd, target, token->next->value, alloc_list))
		{
			ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
			shell->exit_status = 2;
			return (0);
		}
	}
	*current = token->next;
	return (1);
}

int	handle_token_redirection_or_arg(t_token **current, t_cmd *cmd,
		t_list *alloc_list, t_shell *shell)
{
	t_token	*token;

	token = *current;
	if (token->type == WORD)
		add_arg_to_cmd(cmd, token->value, alloc_list);
	else if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == APPEND || token->type == HEREDOC)
		return (handle_redirection(current, cmd, alloc_list, shell));
	return (1);
}
