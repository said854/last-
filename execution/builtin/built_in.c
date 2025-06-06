/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/05/28 20:24:14 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_builtin_name(const char *name)
{
	return (!ft_strcmp(name, "cd") || !ft_strcmp(name, "echo")
		|| !ft_strcmp(name, "pwd") || !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "unset") || !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "exit"));
}

int	if_builtin(t_shell *shell, t_list *alloc_list)
{
	pid_t	pid;

	if (shell->cmds->has_pipe)
	{
		pid = fork();
		if (pid == 0)
		{
			if ((shell->cmds->infiles || shell->cmds->outfiles)
				&& in_out(shell))
				exit(1);
			exit(exec_builtin(&shell, shell->cmds, alloc_list));
		}
		update_exit_status(shell, pid);
	}
	else
	{
		if ((shell->cmds->infiles || shell->cmds->outfiles) && in_out(shell))
		{
			shell->exit_status = 1;
			return (0);
		}

		exec_builtin(&shell, shell->cmds, alloc_list);
	}
	return (EXIT_SUCCESS);
}


int	exec_builtin(t_shell **shell, t_cmd *cmd, t_list *alloc_list)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		(*shell)->exit_status = execute_cd(cmd,
				&(*shell)->env, alloc_list);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		(*shell)->exit_status = execute_echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		(*shell)->exit_status = execute_pwd(cmd);
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (execute_export(shell, alloc_list));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (excute_unset(shell, alloc_list));
	else if (!ft_strcmp(cmd->args[0], "env"))
		(*shell)->exit_status = execute_env(cmd, (*shell)->env);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		execute_exit((*shell), alloc_list);
	return ((*shell)->exit_status);
}
