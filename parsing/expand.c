/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:25:46 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/28 10:43:59 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	should_expand_dollar(char *str)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (str[i] == '$' && !in_single)
			return (1);
		i++;
	}
	return (0);
}

t_token	*split_expanded(char *str, t_list *alloc_list)
{
	char	**parts;
	t_token	*head;
	t_token	*new_token;
	int		i;

	parts = ft_split(str, ' ', alloc_list);
	if (!parts)
		return (NULL);
	head = NULL;
	i = 0;
	while (parts[i])
	{
		if (parts[i][0] == '\0') 
		{
			i++;
			continue;
		}
		new_token = create_token(parts[i], WORD, alloc_list);
		if (!new_token)
			return (NULL);
		append_token(&head, new_token);
		i++;
	}
	return (head);
}


void	fill_unquoted(char *result, const char *str, int *in_single,
		int *in_double)
{
	int (i), (j);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' && !(*in_single))
		{
			*in_double = !(*in_double);
			i++;
		}
		else if (str[i] == '\'' && !(*in_double))
		{
			*in_single = !(*in_single);
			i++;
		}
		else if (str[i] == '\\' && str[i + 1])
		{
			i++;
			result[j++] = str[i++];
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
}

char	*remove_quotes(const char *str, t_list *alloc_list)
{
	char	*result;
	int		in_double;
	int		in_single;

	in_double = 0;
	in_single = 0;
	result = ft_malloc(ft_strlen(str) + 1, &alloc_list);
	if (!result)
		return (NULL);
	fill_unquoted(result, str, &in_single, &in_double);
	return (result);
}

t_heredoc_tmp	*alloc_array(t_heredoc_tmp *old, int new_count,
		t_list *alloc_list)
{
	t_heredoc_tmp	*new_array;
	int				i;

	new_array = ft_malloc(sizeof(t_heredoc_tmp) * new_count, &alloc_list);
	i = 0;
	if (!old)
		return (new_array);
	while (i < new_count - 1)
	{
		new_array[i] = old[i];
		i++;
	}
	return (new_array);
}
