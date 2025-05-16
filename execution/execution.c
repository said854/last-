/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/05/16 15:42:48 by sjoukni          ###   ########.fr       */
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


static void exec_child(t_shell *shell, char *cmd)
{
	int error = 0;

	if (shell->cmds->heredoc_delim)
	{
		dup2(shell->cmds->heredoc_fd, STDIN_FILENO);
		close(shell->cmds->heredoc_fd);
	}
	else if (shell->cmds->infiles)
		error |= open_all_infiles(shell->cmds->infiles);

	if (shell->cmds->outfiles)
		error |= open_all_outfiles(shell->cmds->outfiles, shell->cmds->append_flags);

	if (error)
		exit(EXIT_FAILURE);

	execve(cmd, &shell->cmds->args[0], shell->envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
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
					open_all_outfiles(shell->cmds->outfiles, shell->cmds->append_flags);
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

int	if_path(t_shell *shell)
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

int open_all_infiles(char **infiles)
{
	int fd = -1;
	int i = 0;
	int error = 0;

	while (infiles && infiles[i])
	{
		fd = open(infiles[i], O_RDONLY);
		if (fd < 0)
		{
			perror(infiles[i]);
			error = 1;
		}
		else
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		i++;
	}
	return error;
}

int open_all_outfiles(char **outfiles, int *append_flags)
{
	int fd = -1;
	int i = 0;
	int flags;
	int error = 0;

	while (outfiles && outfiles[i])
	{
		flags = O_WRONLY | O_CREAT;
		flags |= (append_flags[i]) ? O_APPEND : O_TRUNC;

		fd = open(outfiles[i], flags, 0644);
		if (fd < 0)
		{
			perror(outfiles[i]);
			error = 1;
		}
		else
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		i++;
	}
	return error;
}


static void exec_command(t_shell *shell, char **paths, t_list **alloc_list)
{
	pid_t	pid;
	char	*cmd;

	if (if_path(shell))
		return;
	if (if_builtin(shell, (*alloc_list)))
		return ;
	cmd = check_cmd(paths, shell->cmds->args[0], (*alloc_list));
	if (cmd)
	{
		pid = fork();
		if (pid == 0)
			exec_child(shell, cmd);
		else
			update_exit_status(shell, pid);
	}
	else
		set_cmd_not_found(shell, shell->cmds->args[0]);
}

void execution_part(t_shell *shell, t_list **alloc_list)
{
	char **paths;

	if (!shell->cmds)
		return;

	paths = get_paths(&shell, (*alloc_list));
	while (shell->cmds)
	{
		/*add
		if (shell->cmds->heredocs)
		{
			if (!read_heredoc(shell->cmds, shell, *alloc_list))
			{
				sigint_heredoc_handler(shell);
				return; 
			}
		}
		*/
		if (shell->cmds->has_pipe)
		{
			pipex(&shell, (*alloc_list));
			while (shell->cmds && shell->cmds->has_pipe)
				shell->cmds = shell->cmds->next;
			if (shell->cmds)
				shell->cmds = shell->cmds->next;
			continue;
		}

		exec_command(shell, paths, alloc_list);
		shell->cmds = shell->cmds->next;
	}

}

