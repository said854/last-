/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:45:40 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/26 17:11:30 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_token_end(char c, int in_squote, int in_dquote)
{
	if (in_squote || in_dquote)
		return (0);
	if (c == ';' || ft_isspace(c) || is_operator(c))
		return (1);
	return (0);
}

int	handle_quotes(char *line, int *i, int *squote, int *dquote)
{
	if (line[*i] == '\'' && *dquote == 0)
	{
		*squote = !(*squote);
		(*i)++;
		return (1);
	}
	if (line[*i] == '"' && *squote == 0)
	{
		*dquote = !(*dquote);
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_backslash(char *line, int *i)
{
	if (!line[*i + 1])
		return (-3);
	*i += 2;
	return (0);
}

int	check_semicolon(char *line, int i)
{
	if (line[i] == ';')
	{
		if (line[i + 1] == ';')
			return (-2);
		return (1);
	}
	return (0);
}

int	check_operator(char *line, int i)
{
	if (is_operator(line[i]))
	{
		if (is_operator(line[i + 1]) && line[i] == line[i + 1]
			&& line[i] != '|')
			return (2);
		return (1);
	}
	return (0);
}
