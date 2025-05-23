/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/05/22 21:31:48 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	err_cd(char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

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
		free (old_pwd);
		return (err_cd(cmd->args[1]), EXIT_FAILURE);
	}
	update_env(env, "OLDPWD", old_pwd, alloc_list);
	free (old_pwd);
	new_pwd = getcwd(NULL, 0);
	update_env(env, "PWD", new_pwd, alloc_list);
	free (new_pwd);
	return (EXIT_SUCCESS);
}
