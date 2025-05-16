/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:01:24 by hakader           #+#    #+#             */
/*   Updated: 2025/05/05 14:22:38 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <string.h>

void	update_env(t_env **env, char *key, char *replace, t_list *alloc_list)
{
	t_env	*tmp;

	if (!key || !replace)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			tmp->value = ft_strdup(replace, alloc_list);
			free (replace);
			return ;
		}
		tmp = tmp->next;
	}
}
