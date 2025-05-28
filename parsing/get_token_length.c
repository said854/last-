/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_length.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:30:40 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/28 12:32:54 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_spaces_and_check_specials(char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (check_semicolon(line, *i))
		return (check_semicolon(line, *i));
	if (check_operator(line, *i))
		return (check_operator(line, *i));
	return (0);
}

int	handle_token_loop(char *line, int *i, int *squote, int *dquote)
{
	while (line[*i])
	{
		if (line[*i] == '`')
			return (-4);
		if (handle_quotes(line, i, squote, dquote))
			continue ;
		if (line[*i] == '\\')
		{
			if (handle_backslash(line, i))
				return (-3);
		}
		else if (is_token_end(line[*i], *squote, *dquote))
			break ;
		else
			(*i)++;
	}
	return (0);
}

int	get_token_length(char *line, int i)
{
	int	start;
	int	squote;
	int	dquote;
	int	special;
	int	loop_result;

	squote = 0;
	dquote = 0;
	special = skip_spaces_and_check_specials(line, &i);
	// printf("num is %d\n", special);
	if (special)
		return (special);
	start = i;
	loop_result = handle_token_loop(line, &i, &squote, &dquote);
	if (loop_result)
		return (loop_result);
	if (squote || dquote)
		return (-1);
	return (i - start);
}
