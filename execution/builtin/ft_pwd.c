/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:57:57 by hakader           #+#    #+#             */
/*   Updated: 2025/05/16 16:58:11 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_pwd(t_cmd *cmd)
{
	char	*cwd;

	if (count_args(cmd->args) > 1)
	{
		put_error("pwd: too many arguments");
		return (EXIT_FAILURE);
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
	{
		free (cmd);
		perror("pwd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
