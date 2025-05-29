/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:36:31 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/29 15:41:08 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	update_last_token_and_heredoc(t_token *head,
											t_token **last_token,
											int *prev_is_heredoc)
{
	*last_token = head;
	while (*last_token && (*last_token)->next)
		*last_token = (*last_token)->next;
	*prev_is_heredoc = (*last_token && (*last_token)->type == HEREDOC);
}
int	is_redirect_type(t_token_type type)
{
	return (type == APPEND || type == REDIR_OUT || type == REDIR_IN);
}

int	is_ambiguous_redirect(t_token *last_token, char *expanded_value)
{
	if (!last_token || !is_redirect_type(last_token->type))
		return (0);

	if (!expanded_value || expanded_value[0] == '\0')
		return (1);
	int i = 0;
	while (expanded_value[i])
	{
		if (ft_isspace(expanded_value[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	handle_expansion_and_continue(
	char *token_str, t_shell *shell, t_token **head, t_list *alloc_list,
	t_token *last_token)
{
	char	*expanded;
	t_token	*expanded_tokens;
	expanded = expand_token_value(token_str, shell, alloc_list);
	if (is_ambiguous_redirect(last_token, expanded))
	{
		ft_putstr_fd( "minishell: ambiguous redirect\n", 2);
		shell->exit_status = 1;
		return (0); 
	}
	expanded_tokens = split_expanded(expanded, alloc_list);
	if (!*head)
		*head = expanded_tokens;
	else
		append_token(head, expanded_tokens);
	return (1);
}


t_token	*tokenize_line(t_shell *shell, char *line, t_list *alloc_list)
{
	int				i;
	t_token			*head;
	t_token			*last_token;
	t_token			*current_token;
	char			*token_str;
	t_token_type	type;
	int				len;
	int				prev_is_heredoc;

	i = 0;
	head = NULL;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		len = get_token_length(line, i);
		if (len < 0)
			return (return_syntax(shell, len));
		token_str = ft_strndup(line + i, len, alloc_list);
		type = get_token_type(token_str);
		update_last_token_and_heredoc(head, &last_token, &prev_is_heredoc);
		if (type == WORD && !prev_is_heredoc && should_expand_dollar(token_str))
		{
			char *expanded = expand_token_value(token_str, shell, alloc_list);
			if (is_ambiguous_redirect(last_token, expanded))
			{
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				shell->exit_status = 1;
				return NULL;
			}
			t_token *expanded_tokens = split_expanded(expanded, alloc_list);
			if (expanded_tokens)
			{
				if (!head)
					head = expanded_tokens;
				else
					append_token(&head, expanded_tokens);
			}
			i += len;
			continue;
		}
		
		current_token = create_token(token_str, type, alloc_list);
		append_token(&head, current_token);
		i += len;
	}
	return (head);
}
