/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:00:37 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/20 15:32:20 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execution.h"

static void	handle_infiles(t_cmd *cmd, t_list *alloc_list)
{
	int		fd;
	int		tmp_fd;
	int		i;

	fd = -1;
	i = 0;
	while (cmd->infiles && cmd->infiles[i])
	{
		tmp_fd = open(cmd->infiles[i], O_RDONLY);
		if (tmp_fd < 0)
		{
			perror(cmd->infiles[i]);
			free_all(&alloc_list);
			exit(EXIT_FAILURE);
		}
		if (!cmd->infiles[i + 1])
			fd = tmp_fd;
		else
			close(tmp_fd);
		i++;
	}
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

static void	handle_outfiles(t_cmd *cmd, t_list *alloc_list)
{
	int	(fd), (tmp_fd), (flags), (i);

	fd = -1;
	i = 0;
	while (cmd->outfiles && cmd->outfiles[i])
	{
		flags = O_WRONLY | O_CREAT;
		if (cmd->append_flags && cmd->append_flags[i] == 1)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		tmp_fd = open(cmd->outfiles[i], flags, 0644);
		if (tmp_fd < 0)
		{
			perror(cmd->outfiles[i]);
			free_all(&alloc_list);
			exit(EXIT_FAILURE);
		}
		if (!cmd->outfiles[i + 1])
			fd = tmp_fd;
		else
			close(tmp_fd);
		i++;
	}
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

void exec_pipeline_cmd(t_shell *shell, t_cmd *cmd, char **paths, int in_fd,
						int out_fd, t_list *alloc_list)
{
	char *cmd_path;

	set_child_signals();
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	handle_redirections(cmd, alloc_list);

	if (!cmd->args || !cmd->args[0])
		exit(EXIT_SUCCESS);

	if (is_builtin_name(cmd->args[0]))
		exit(exec_builtin(&shell, alloc_list));

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

void pipex(t_shell **shell, t_list *alloc_list)
{
	int		pipe_fd[2];
	int		in_fd = dup(STDIN_FILENO);
	int		prev_fd = in_fd;
	pid_t	pid;
	char	**paths = get_paths(shell, alloc_list);
	t_cmd	*current = (*shell)->cmds;

	while (current && current->has_pipe)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == 0)
		{
			close(pipe_fd[0]);
			exec_pipeline_cmd(*shell, current, paths, prev_fd, pipe_fd[1], alloc_list);
		}
		close(pipe_fd[1]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = pipe_fd[0];
		current = current->next;
	}

	if (current)
	{
		pid = fork();
		if (pid == 0)
			exec_pipeline_cmd(*shell, current, paths, prev_fd, STDOUT_FILENO, alloc_list);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
	}
	int status;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			(*shell)->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			(*shell)->exit_status = 128 + WTERMSIG(status);
		else
			(*shell)->exit_status = 1;
	}


}