/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:56:41 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/26 16:38:35 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**append_str_array(char **arr, char *new_str, t_list *alloc_list)
{
	char	**new_arr;

	int (i), (j);
	i = 0;
	while (arr && arr[i])
		i++;
	new_arr = ft_malloc(sizeof(char *) * (i + 2), &alloc_list);
	if (!new_arr)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_arr[j] = arr[j];
		j++;
	}
	new_arr[i] = new_str;
	new_arr[i + 1] = NULL;
	return (new_arr);
}

int	get_int_array_length(int *arr)
{
	int	i;

	i = 0;
	while (arr && (arr[i] == 0 || arr[i] == 1))
		i++;
	return (i);
}

int	*append_int_array(int *arr, int value, t_list *alloc_list)
{
	int	*new_arr;

	int (i), (j);
	i = get_int_array_length(arr);
	new_arr = ft_malloc(sizeof(int) * (i + 2), &alloc_list);
	if (!new_arr)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_arr[j] = arr[j];
		j++;
	}
	new_arr[i] = value;
	new_arr[i + 1] = -1;
	return (new_arr);
}

int	is_cmd_empty(t_cmd *cmd)
{
	return (!cmd->args && !cmd->infiles && !cmd->outfiles
		&& !cmd->heredoc_delim);
}
