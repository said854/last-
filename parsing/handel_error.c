/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:46:03 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/13 10:43:50 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_redirection(t_token_type type)
{
    return (type == REDIR_OUT || type == REDIR_IN || type == APPEND || type == HEREDOC);
}
int	print_error(char *message)
{
	ft_putstr_fd("syntax error: ", 2);
	ft_putstr_fd(message, 2);
	return (EXIT_SUCCESS);
}

int check_syntax(t_token *token_list)
{
    t_token *current = token_list;
    t_token *prev = NULL;

    if (!current)
        return 0;
    if (current->type == PIPE)
        return (print_error("near unexpected token `|`"));
    while (current)
    {
        if (prev && prev->type == PIPE && current->type == PIPE)
            return (print_error("near unexpected token `|`"));

        if (is_redirection(current->type))
        {
            if (!current->next || current->next->type != WORD)
                return (print_error ("missing filename after redirection"));
        }

        prev = current;
        current = current->next;
    }
    if (prev && prev->type == PIPE)
        return (print_error ("unexpected end of input after `|`"));

    return (EXIT_FAILURE);
}

