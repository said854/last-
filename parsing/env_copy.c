/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:08:35 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/13 10:40:33 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*key(char *str, t_list *alloc_list)
{
	char	*key;

	int (i), (j);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_malloc((i + 1), &alloc_list);
	if (!key)
		return (NULL);
	j = 0;
	while (j < i)
	{
		key[j] = str[j];
		j++;
	}
	key[i] = '\0';
	return (key);
}

char	*value(char *str, t_list *alloc_list)
{
	char	*value;

	int (i), (len), (j);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	len = 0;
	while (str[i + len])
		len++;
	value = ft_malloc((len + 1), &alloc_list);
	if (!value)
		return (NULL);
	j = 0;
	while (j < len)
	{
		value[j] = str[i + j];
		j++;
	}
	value[len] = '\0';
	return (value);
}

t_env	*env_copy(char *content, t_list	*alloc_list)
{
	t_env	*new_node;

	if (!content || !ft_strchr(content, '='))
		return (NULL);
	new_node = ft_malloc(sizeof(t_env), &alloc_list);
	if (!new_node)
		return (NULL);
	new_node->key = key(content, alloc_list);
	new_node->value = value(content, alloc_list);
	new_node->next = NULL;
	return (new_node);
}

void	append_env(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}
