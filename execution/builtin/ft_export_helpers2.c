/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:32:21 by hakader           #+#    #+#             */
/*   Updated: 2025/05/26 17:13:38 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*get_value(char *arg, t_list *alloc_list)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1, alloc_list));
}

char	*get_key(char *arg, t_list *alloc_list)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i, alloc_list));
}

void	print_list_env(t_env **head, t_list *alloc_list)
{
	t_env	*sorted = copy_env(*head, alloc_list);
	t_env	*i = sorted;
	t_env	*j;

	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->key, j->key) > 0)
				swap_env(i, j);
			j = j->next;
		}
		i = i->next;
	}
	while (sorted)
	{
		if (sorted->value)
			printf("declare -x %s=\"%s\"\n", sorted->key, sorted->value);
		else
			printf("declare -x %s\n", sorted->key);
		sorted = sorted->next;
	}
}
