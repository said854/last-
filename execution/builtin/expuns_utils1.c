/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expuns_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 02:53:36 by hakader           #+#    #+#             */
/*   Updated: 2025/05/01 12:03:07 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// int	is_valid_key(const char *str)
// {
// 	int	i;

// 	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
// 		return (0);
// 	i = 1;
// 	while (str[i] && str[i] != '=')
// 	{
// 		if (!ft_isalnum(str[i]) && str[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// t_env	*find_env(t_env *env, const char *key)
// {
// 	while (env)
// 	{
// 		if (!ft_strcmp(env->key, key))
// 			return (env);
// 		env = env->next;
// 	}
// 	return (NULL);
// }

// char	*extract_key(const char *str)
// {
// 	int		i;
// 	char	*key;

// 	i = 0;
// 	while (str[i] && str[i] != '=')
// 		i++;
// 	key = malloc(i + 1);
// 	if (!key)
// 		return (NULL);
// 	strncpy(key, str, i);
// 	key[i] = '\0';
// 	return (key);
// }

// char	*extract_value(const char *str)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i] && str[i] != '=')
// 		i++;
// 	if (!str[i])
// 		return (NULL);
// 	return (ft_strdup(&str[i + 1]));
// }

// void	add_or_update_env(t_env **env, char *arg)
// {
// 	t_env	*found;
// 	char	*key;
// 	char	*value;
// 	t_env	*new;

// 	key = extract_key(arg);
// 	value = extract_value(arg);
// 	found = find_env(*env, key);
// 	if (found)
// 	{
// 		free(found->value);
// 		found->value = value;
// 	}
// 	else
// 	{
// 		new = malloc(sizeof(t_env));
// 		new->key = key;
// 		new->value = value;
// 		new->next = *env;
// 		*env = new;
// 	}
// }
