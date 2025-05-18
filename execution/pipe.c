/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:00:37 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/18 16:41:14 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execution.h"


void handle_redirections(t_cmd *cmd)
{
	int fd;
	int i;

	fd = -1;
	i = 0;
	while (cmd->infiles && cmd->infiles[i])
	{
		int tmp_fd = open(cmd->infiles[i], O_RDONLY);
		if (tmp_fd < 0)
		{
			perror(cmd->infiles[i]);
			exit(EXIT_FAILURE);
		}
		if (cmd->infiles[i + 1] == NULL)
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

	fd = -1;
	i = 0;
	while (cmd->outfiles && cmd->outfiles[i])
	{
		int flags = O_WRONLY | O_CREAT;
		if (cmd->append_flags && cmd->append_flags[i] == 1)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;

		int tmp_fd = open(cmd->outfiles[i], flags, 0644);
		if (tmp_fd < 0)
		{
			perror(cmd->outfiles[i]);
			exit(EXIT_FAILURE);
		}
		if (cmd->outfiles[i + 1] == NULL)
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

void exec_pipeline_cmd(t_shell *shell, t_cmd *cmd, char **paths, int in_fd,
						int out_fd, t_list *alloc_list)
{
	char *cmd_path;

	set_child_signals();
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	handle_redirections(cmd);

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
	while (wait(NULL) > 0)
		;
}