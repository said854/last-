/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:17:34 by hakader           #+#    #+#             */
/*   Updated: 2025/05/23 16:17:55 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	open_fail_exit(char *file, t_list *alloc_list)
{
	perror(file);
	free_all(&alloc_list);
	exit(EXIT_FAILURE);
}

static void	open_infiles(t_cmd *cmd, t_list *alloc_list, int *fd)
{
	int		tmp_fd;
	int		i;

	*fd = -1;
	i = 0;
	while (cmd->infiles && cmd->infiles[i])
	{
		tmp_fd = open(cmd->infiles[i], O_RDONLY);
		if (tmp_fd < 0)
			open_fail_exit(cmd->infiles[i], alloc_list);
		if (!cmd->infiles[i + 1])
			*fd = tmp_fd;
		else
			close(tmp_fd);
		i++;
	}
}

static void	handle_infiles(t_cmd *cmd, t_list *alloc_list)
{
	int	fd;

	open_infiles(cmd, alloc_list, &fd);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

static int	get_outfile_flags(t_cmd *cmd, int i)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd->append_flags && cmd->append_flags[i] == 1)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

static void	open_outfiles(t_cmd *cmd, t_list *alloc_list, int *fd)
{
	int	tmp_fd;
	int	flags;
	int	i;

	*fd = -1;
	i = 0;
	while (cmd->outfiles && cmd->outfiles[i])
	{
		flags = get_outfile_flags(cmd, i);
		tmp_fd = open(cmd->outfiles[i], flags, 0644);
		if (tmp_fd < 0)
			open_fail_exit(cmd->outfiles[i], alloc_list);
		if (!cmd->outfiles[i + 1])
			*fd = tmp_fd;
		else
			close(tmp_fd);
		i++;
	}
}

static void	handle_outfiles(t_cmd *cmd, t_list *alloc_list)
{
	int	fd;

	open_outfiles(cmd, alloc_list, &fd);
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	handle_redirections(t_cmd *cmd, t_list *alloc_list)
{
	handle_infiles(cmd, alloc_list);
	handle_outfiles(cmd, alloc_list);
}

void	exec_pipeline_cmd(t_shell *shell, t_cmd *cmd,
	char **paths, int in_fd, int out_fd, t_list *alloc_list)
{
	char	*cmd_path;

	set_child_signals();
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	handle_redirections(cmd, alloc_list);
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_SUCCESS);
	if (is_builtin_name(cmd->args[0]))
		exit(exec_builtin(&shell, cmd, alloc_list));
	cmd_path = check_cmd(paths, cmd->args[0], alloc_list);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: command not found\n", cmd->args[0]);
		exit(127);
	}
	execve(cmd_path, cmd->args, shell->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	handle_pipe(t_shell **shell, t_list *alloc_list,
	t_cmd *cmd, int *prev_fd, char **paths)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		exec_pipeline_cmd(*shell, cmd, paths, *prev_fd, pipe_fd[1], alloc_list);
	}
	close(pipe_fd[1]);
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	*prev_fd = pipe_fd[0];
}

static void	wait_for_children(pid_t last_pid, t_shell **shell)
{
	int		status;
	pid_t	wpid;

	while ((wpid = waitpid(-1, &status, 0)) > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				(*shell)->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				(*shell)->exit_status = 128 + WTERMSIG(status);
			else
				(*shell)->exit_status = 1;
		}
	}
}

void	pipex(t_shell **shell, t_list *alloc_list)
{
	t_cmd	*cmd;
	char	**paths;
	int		prev_fd;
	pid_t	pid;

	paths = get_paths(shell, alloc_list);
	prev_fd = dup(STDIN_FILENO);
	cmd = (*shell)->cmds;
	while (cmd && cmd->has_pipe)
	{
		handle_pipe(shell, alloc_list, cmd, &prev_fd, paths);
		cmd = cmd->next;
	}
	if (cmd)
	{
		pid = fork();
		if (pid == 0)
			exec_pipeline_cmd(*shell, cmd, paths, prev_fd, STDOUT_FILENO, alloc_list);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		wait_for_children(pid, shell);
	}
}
