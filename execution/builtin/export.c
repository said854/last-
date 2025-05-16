/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:58:09 by hakader           #+#    #+#             */
/*   Updated: 2025/05/13 10:52:28 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_env *ft_new_env(char *key, char *value, t_list *alloc_list)
{
	t_env *new = ft_malloc(sizeof(t_env), &alloc_list);
	if (!new)
		return (NULL);
	new->key = ft_strdup(key, alloc_list);
	new->value = ft_strdup(value, alloc_list);
	new->next = NULL;
	return (new);
}

void ft_envadd_back(t_env **env, char *key, char *value, t_list *alloc_list)
{
	t_env *new = ft_new_env(key, value, alloc_list);
	t_env *last;

	if (!env || !new)
		return ;
	if (*env == NULL)
	{
		*env = new;
		return;
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new;
}

int	check_exp(t_shell *shell)
{
	if (!shell->cmds->args[1])
	{
		print_list_env(&(shell->env));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
