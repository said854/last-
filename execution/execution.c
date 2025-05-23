/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/05/23 12:36:50 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	path_cmd(t_shell **shell)
{
	pid_t	pid;

	if ((*shell)->cmds->args[0][0] == '/')
	{
		if (access((*shell)->cmds->args[0], X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve((*shell)->cmds->args[0],
					&(*shell)->cmds->args[0], (*shell)->envp);
			}
			else
				update_exit_status((*shell), pid);
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	exec_child(t_shell *shell, char *cmd, t_list **alloc_list)
{
	int	error;

	error = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	if (shell->cmds->heredoc_delim)
	{
		if (shell->cmds->heredoc_fd == -1)
			exit(shell->exit_status);
		dup2(shell->cmds->heredoc_fd, STDIN_FILENO);
		close(shell->cmds->heredoc_fd);
	}
	else if (shell->cmds->infiles)
		error |= open_all_infiles(shell);
	if (error)
		exit(EXIT_FAILURE);
	if (shell->cmds->outfiles)
		error |= open_all_outfiles(shell);
	if (error)
	{
		shell->cmds = shell->cmds->next;
		exit(EXIT_FAILURE);
	}
	execve(cmd, &shell->cmds->args[0], shell->envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

int	if_path(t_shell *shell, t_list **alloc_list)
{
	pid_t	pid;
	t_cmd	*cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->args && cmd->args[0] && access(cmd->args[0], X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(cmd->args[0], cmd->args, shell->envp);
				exit(EXIT_FAILURE);
			}
			else
				update_exit_status(shell, pid);
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

static void	exec_command(t_shell *shell, char **paths, t_list **alloc_list)
{
	pid_t		pid;
	char		*cmd;
	struct stat	sa;

	if (stat(shell->cmds->args[0], &sa) == 0 && S_ISDIR(sa.st_mode)
		&& strchr(shell->cmds->args[0], '/'))
		return (err_dir(shell));
	if (if_builtin(shell, (*alloc_list)))
		return ;
	cmd = check_cmd(paths, shell->cmds->args[0], (*alloc_list));
	if (cmd)
	{
		pid = fork();
		if (pid == 0)
			exec_child(shell, cmd, alloc_list);
		else
			update_exit_status(shell, pid);
	}
	else
		set_cmd_not_found(shell, shell->cmds->args[0]);
}

void	execution_part(t_shell *shell, t_list **alloc_list)
{
	char	**paths;

	if (!shell->cmds || !shell->cmds->args || !shell->cmds->args[0])
		return ;
	paths = get_paths(&shell, (*alloc_list));
	while (shell->cmds)
	{
		if (shell->cmds->heredocs)
		{
			shell->from_here_doc = 1;
			if (!read_heredoc(shell->cmds, shell, *alloc_list))
			{
				return (sigint_heredoc_handler(shell->exit_status));
			}
		}
		if (shell->cmds->has_pipe)
		{
			pipex(&shell, (*alloc_list));
			while (shell->cmds && shell->cmds->has_pipe)
				shell->cmds = shell->cmds->next;
			if (shell->cmds)
				shell->cmds = shell->cmds->next;
			continue ;
		}
		exec_command(shell, paths, alloc_list);
		shell->cmds = shell->cmds->next;
	}
}
