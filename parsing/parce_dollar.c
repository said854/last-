/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:30:42 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/27 21:48:06 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_dollar_pos(char *str)
{
	int	i;

	i = 0;
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

char	*extract_var_name(char *str, int pos, t_list *alloc_list)
{
	int	start;
	int	len;

	start = pos + 1;
	len = 0;
	if (str[start] == '?')
		return (ft_strdup("?", alloc_list));
	while (str[start + len]
		&& (ft_isalpha(str[start + len])
			|| ft_isdigit(str[start + len])
			|| str[start + len] == '_'))
		len++;
	if (len == 0)
		return (NULL);
	return (ft_substr(str, start, len, alloc_list));
}

char	*get_env_value(t_shell *shell, char *key, t_list *alloc_list)
{
	t_env	*tmp;

	if (!strcmp(key, "?"))
		return (ft_itoa(shell->exit_status, alloc_list));
	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (ft_strdup(tmp->value, alloc_list));
		tmp = tmp->next;
	}
	return (0);
}

char	*replace_var_in_string(char *src, int var_start, int var_len,
		char *value, t_list *alloc_list)
{
	int		(before_len);
	int		(value_len);
	int		(after_len);
	int		total_len;
	char	*new_str;
	int		i;
	int		j;

	before_len = var_start;
	value_len = ft_strlen(value);
	after_len = ft_strlen(src + var_start + var_len + 1);
	total_len = before_len + value_len + after_len;
	new_str = ft_malloc((total_len + 1), &alloc_list);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < before_len)
	{
		new_str[i] = src[i];
		i++;
	}
	j = 0;
	while (j < value_len)
		new_str[i++] = value[j++];
	j = var_start + var_len + 1;
	while (src[j])
		new_str[i++] = src[j++];
	new_str[i] = '\0';
	return (new_str);
}

char	*expand_token_value(char *value, t_shell *shell, t_list *alloc_list)
{
	int		i = 0;
	char	*result = ft_strdup("", alloc_list);
	char	*var_name;
	char	*var_value;
	char	*tmp;
	int		start;

	while (value[i])
	{
		if (value[i] == '$')
		{
			start = i++;
			if (value[i] == '?')
			{
				var_value = ft_itoa(shell->exit_status, alloc_list);
				i++;
			}
			else if (ft_isalpha(value[i]) || value[i] == '_')
			{
				int var_len = 0;
				while (value[i + var_len] &&
					(ft_isalnum(value[i + var_len]) || value[i + var_len] == '_'))
					var_len++;

				var_name = ft_substr(value, i, var_len, alloc_list);
				var_value = get_env_value(shell, var_name, alloc_list);
				if (!var_value)
					var_value = ft_strdup("", alloc_list);
				i += var_len;
			}
			else
			{
				var_value = ft_strdup("$", alloc_list);
			}

			tmp = ft_strjoin(result, var_value, alloc_list);
			result = tmp;
		}
		else
		{
			char buf[2] = { value[i], 0 };
			tmp = ft_strjoin(result, buf, alloc_list);
			result = tmp;
			i++;
		}
	}
	return result;
}


// static char	*expand_exit_status(char *result, int pos,
// 	t_shell *shell, t_list *alloc_list)
// {
// 	char	*value;
// 	char	*new_result;

// 	value = ft_itoa(shell->exit_status, alloc_list);
// 	new_result = replace_var_in_string(result, pos, 1, value, alloc_list);
// 	return (new_result);
// }

// static char	*expand_env_var(char *result, int pos,
// 	t_shell *shell, t_list *alloc_list)
// {
// 	char	*var;
// 	char	*value;
// 	char	*new_result;

// 	var = extract_var_name(result, pos, alloc_list);
// 	if (!var)
// 		return (result);
// 	value = get_env_value(shell, var, alloc_list);
// 	new_result = replace_var_in_string(result, pos, ft_strlen(var),
// 			value, alloc_list);
// 	return (new_result);
// }

// char	*expand_token_value(char *value, t_shell *shell, t_list *alloc_list)
// {
// 	char	*result;
// 	int		pos;

// 	result = ft_strdup(value, alloc_list);
// 	while ((pos = get_dollar_pos(result)) != -1)
// 	{
// 		if (result[pos + 1] == '?')
// 			result = expand_exit_status(result, pos, shell, alloc_list);
// 		else
// 			result = expand_env_var(result, pos, shell, alloc_list);
// 	}
// 	return (result);
// }

