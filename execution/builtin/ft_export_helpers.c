/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:08:28 by hakader           #+#    #+#             */
/*   Updated: 2025/05/26 17:51:38 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_env	*copy_env(t_env *env, t_list *alloc_list)
{
	t_env	*copy;

	copy = NULL;
	while (env)
	{
		ft_envadd_back(&copy, env->key, env->value, alloc_list);
		env = env->next;
	}
	return (copy);
}

void	swap_env(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_val;

	tmp_val = a->value;
	tmp_key = a->key;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_val;
}

int	check_exp(t_shell *shell, t_list *alloc_list)
{
	if (check_options(shell->cmds, "export"))
	{
		shell->exit_status = 1;
		return (EXIT_FAILURE);
	}
	if (!shell->cmds->args[1])
	{
		print_list_env(&(shell->env), alloc_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	is_valid_key(char *s)
{
	int	i;

	i = 0;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[i])
	{
		if (s[i] == '=')
			break ;
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

void	non_valide(t_shell **shell, char *identifier)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	(*shell)->exit_status = 1;
}
