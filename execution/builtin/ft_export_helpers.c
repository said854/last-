/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:08:28 by hakader           #+#    #+#             */
/*   Updated: 2025/05/16 17:30:11 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	check_exp(t_shell *shell)
{
	if (!shell->cmds->args[1])
	{
		print_list_env(&(shell->env));
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

char	*get_key(char *arg, t_list *alloc_list)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i, alloc_list));
}

char	*get_value(char *arg, t_list *alloc_list)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1, alloc_list));
}
