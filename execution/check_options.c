/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:43:05 by hakader           #+#    #+#             */
/*   Updated: 2025/05/26 18:01:39 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	check_options(t_cmd *cmd, char *msg)
{
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '-')
		{
			if (cmd->args[i][1])
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(msg, 2);
				ft_putendl_fd(": no options allowed", 2);
				return (EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
