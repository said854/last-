/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:21:26 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/29 15:42:09 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*create_token(char *str, t_token_type type, t_list *alloc_list)
{
	t_token	*new_token;

	new_token = ft_malloc(sizeof(t_token), &alloc_list);
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(str, alloc_list);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_token **head, t_token *new)
{
	t_token	*temp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_token_type	get_token_type(char *str)
{
	if (!strcmp(str, "|"))
		return (PIPE);
	if (!strcmp(str, ">"))
		return (REDIR_OUT);
	if (!strcmp(str, ">>"))
		return (APPEND);
	if (!strcmp(str, "<"))
		return (REDIR_IN);
	if (!strcmp(str, "<<"))
		return (HEREDOC);
	if (!strcmp(str, ";"))
		return (SEMICOLON);
	return (WORD);
}
