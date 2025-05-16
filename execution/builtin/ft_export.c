/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:59:09 by hakader           #+#    #+#             */
/*   Updated: 2025/05/16 17:28:49 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_env	*ft_new_env(char *key, char *value, t_list *alloc_list)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env), &alloc_list);
	if (!new)
		return (NULL);
	new->key = ft_strdup(key, alloc_list);
	new->value = ft_strdup(value, alloc_list);
	new->next = NULL;
	return (new);
}

void	ft_envadd_back(t_env **env, char *key, char *value, t_list *alloc_list)
{
	t_env	*new;
	t_env	*last;

	new = ft_new_env(key, value, alloc_list);
	if (!env || !new)
		return ;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	update_or_add(t_env **env, char *key, char *value, t_list *alloc_list)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (value)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value, alloc_list);
			}
			return ;
		}
		tmp = tmp->next;
	}
	ft_envadd_back(env, key, value, alloc_list);
}

int	execute_export(t_shell **shell, t_list *alloc_list)
{
	int		i;
	char	*key;
	char	*value;

	if (check_exp((*shell)))
		return (EXIT_FAILURE);
	i = 1;
	while ((*shell)->cmds->args[i])
	{
		if (!is_valid_key((*shell)->cmds->args[i]))
		{
			non_valide(shell, (*shell)->cmds->args[i]);
			i++;
			continue ;
		}
		key = get_key((*shell)->cmds->args[i], alloc_list);
		value = get_value((*shell)->cmds->args[i], alloc_list);
		update_or_add(&((*shell)->env), key, value, alloc_list);
		free(key);
		free(value);
		i++;
	}
	if ((*shell)->exit_status != 1)
		(*shell)->exit_status = 0;
	return (EXIT_FAILURE);
}
