/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/05/17 16:22:30 by sjoukni          ###   ########.fr       */
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

	if (is_builtin_name(shell->cmds->args[0]))
	{
		if (shell->cmds->has_pipe)
		{
			pid = fork();
			if (pid == 0)
			{
				if (shell->cmds->infiles)
					open_all_infiles(shell->cmds->infiles);
				else if (shell->cmds->outfiles)
					open_all_outfiles(shell->cmds->outfiles,
						shell->cmds->append_flags);
				free_all(&alloc_list);
				exit(exec_builtin(&shell, alloc_list));
			}
			else
				update_exit_status(shell, pid);
		}
		else
			exec_builtin(&shell, alloc_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	exec_builtin(t_shell **shell, t_list *alloc_list)
{
	if (!ft_strcmp((*shell)->cmds->args[0], "cd"))
		(*shell)->exit_status = execute_cd((*shell)->cmds,
				&(*shell)->env, alloc_list);
	else if (!ft_strcmp((*shell)->cmds->args[0], "echo"))
		(*shell)->exit_status = execute_echo((*shell)->cmds);
	else if (!ft_strcmp((*shell)->cmds->args[0], "pwd"))
		(*shell)->exit_status = execute_pwd((*shell)->cmds);
	else if (!ft_strcmp((*shell)->cmds->args[0], "export"))
		return (execute_export(shell, alloc_list));
	else if (!ft_strcmp((*shell)->cmds->args[0], "unset"))
		return (excute_unset(shell, alloc_list));
	else if (!ft_strcmp((*shell)->cmds->args[0], "env"))
		(*shell)->exit_status = execute_env((*shell)->cmds, (*shell)->env);
	else if (!ft_strcmp((*shell)->cmds->args[0], "exit"))
		return (execute_exit((*shell), alloc_list));
	return ((*shell)->exit_status);
}
