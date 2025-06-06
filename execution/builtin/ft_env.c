/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:09:35 by hakader           #+#    #+#             */
/*   Updated: 2025/05/26 17:57:38 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_env(t_cmd *cmd, t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	if (count_args(cmd->args) > 1)
	{
		put_error("minishell: env: you have (no arguments / no options)");
		return (EXIT_FAILURE);
	}
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
