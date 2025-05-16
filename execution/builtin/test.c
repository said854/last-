/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:42:18 by hakader           #+#    #+#             */
/*   Updated: 2025/05/13 10:32:39 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_valid_key(char *s)
{
	int	i = 0;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[i])
	{
		if (s[i] == '=')
			break;
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

char	*get_key(char *arg, t_list *alloc_list)
{
	int		i = 0;

	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i, alloc_list));
}

char	*get_value(char *arg, t_list *alloc_list)
{
	char	*equal = ft_strchr(arg, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1, alloc_list));
}

void	update_or_add(t_env **env, char *key, char *value, t_list *alloc_list)
{
	t_env *tmp = *env;

	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (value)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value, alloc_list);
			}
			return;
		}
		tmp = tmp->next;
	}
	ft_envadd_back(env, key, value, alloc_list);
}

void	non_valide(t_shell **shell, char *identifier)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	(*shell)->exit_status = 1;
}

int	execute_export(t_shell **shell, t_list *alloc_list)
{
	int		i = 1;
	char	*key;
	char	*value;

	if (check_exp((*shell)))
		return (1);
	while ((*shell)->cmds->args[i])
	{
		if (!is_valid_key((*shell)->cmds->args[i]))
		{
			non_valide(shell, (*shell)->cmds->args[i]);
			i++;
			continue;
		}
		key = get_key((*shell)->cmds->args[i], alloc_list);
		value = get_value((*shell)->cmds->args[i], alloc_list);
		update_or_add(&((*shell)->env), key, value, alloc_list);
		free(key);
		if (value)
			free(value);
		i++;
	}
	if ((*shell)->exit_status != 1)
		(*shell)->exit_status = 0;
	return (1);
}
