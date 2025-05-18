/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:30:42 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/18 16:33:17 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int get_dollar_pos(char *str)
{
	int i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}


char *extract_var_name(char *str, int pos, t_list *alloc_list)
{
	int start = pos + 1;
	int len = 0;

	if (str[start] == '?')
		return (ft_strdup("?", alloc_list)); 

	while (str[start + len] &&
		(ft_isalpha(str[start + len]) || ft_isdigit(str[start + len]) || str[start + len] == '_'))
	{
		len++;
	}

	if (len == 0)
		return (NULL);
	return ft_substr(str, start, len, alloc_list); 
}
	
char *get_env_value(t_shell *shell, char *key, t_list *alloc_list)
{
	t_env *tmp;

	if (!strcmp(key, "?"))
		return (ft_itoa(shell->exit_status, alloc_list)); 

	tmp = shell->env;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
			return (ft_strdup(tmp->value, alloc_list));
		tmp = tmp->next;
	}
	return (0);
}


char *replace_var_in_string(char *src, int var_start, int var_len,
							char *value, t_list *alloc_list)
{
	int before_len = var_start;
	int value_len = ft_strlen(value);
	int after_len = ft_strlen(src + var_start + var_len + 1);
	int total_len = before_len + value_len + after_len;

	char *new_str = ft_malloc((total_len + 1), &alloc_list);
	if (!new_str)
		return (NULL);

	int i = 0;
	while (i < before_len)
	{
		new_str[i] = src[i];
		i++;
	}

	int j = 0;
	while (j < value_len)
		new_str[i++] = value[j++];

	j = var_start + var_len + 1;
	while (src[j])
		new_str[i++] = src[j++];

	new_str[i] = '\0';
	return new_str;
}

char *expand_token_value(char *value, t_shell *shell, t_list *alloc_list)
{
	char *result = ft_strdup(value, alloc_list);
	int pos;

	while ((pos = get_dollar_pos(result)) != -1)
	{
		if (result[pos + 1] == '?') 
		{
			char *var_value = ft_itoa(shell->exit_status, alloc_list);
			char *expanded = replace_var_in_string(result, pos, 1, var_value, alloc_list); 
			result = expanded;
		}
		else
		{
			char *var = extract_var_name(result, pos, alloc_list);
			if (!var)
			break;
			
			char *var_value = get_env_value(shell, var, alloc_list);
			char *expanded = replace_var_in_string(result, pos, ft_strlen(var), var_value, alloc_list);
			result = expanded;
		}
	}
	return result;
}
