/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/05/19 21:10:20 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_cd(t_cmd *cmd, t_env **env, t_list *alloc_list)
{
	char	*old_pwd;
	char	*new_pwd;

	if (count_args(cmd->args) > 2)
		return ((put_error("cd: too many arguments")), 1);
	if (!cmd->args[1])
	{
		put_error("please type relative or absolute path");
		return (EXIT_FAILURE);
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(cmd->args[1]) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	update_env(env, "OLDPWD", old_pwd, alloc_list);
	new_pwd = getcwd(NULL, 0);
	update_env(env, "PWD", new_pwd, alloc_list);
	return (EXIT_SUCCESS);
}
