/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:01:14 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/17 22:29:19 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	write_heredoc_loop(int i, int fd, t_cmd *cmd, t_shell *shell,
		t_list *alloc_list)
{
	char	*line;
	char	*old;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, cmd->heredocs[i].delim))
			break ;
		if (cmd->heredocs[i].expand)
		{
			old = line;
			line = expand_token_value(line, shell, alloc_list);
			free(old);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
}

int	handle_heredoc_child(int i, int *pipe_fd, t_cmd *cmd, t_shell *shell,
		t_list *alloc_list)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[0]);
	write_heredoc_loop(i, pipe_fd[1], cmd, shell, alloc_list);
	close(pipe_fd[1]);
	exit(0);
}

int	read_heredoc(t_cmd *cmd, t_shell *shell, t_list *alloc_list)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	int		i;

	i = 0;
	while (i < cmd->heredoc_count)
	{
		if (pipe(pipe_fd) == -1 || (pid = fork()) == -1)
			return (perror("heredoc"), 0);
		if (pid == 0)
			handle_heredoc_child(i, pipe_fd, cmd, shell, alloc_list);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, SIG_DFL);
		close(pipe_fd[1]);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			return (shell->exit_status = 130, close(pipe_fd[0]), 0);
		if (i == cmd->heredoc_count - 1)
			cmd->heredoc_fd = pipe_fd[0];
		else
			close(pipe_fd[0]);
		i++;
	}
	return (1);
}
