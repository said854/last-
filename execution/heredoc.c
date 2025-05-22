/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:01:14 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/20 20:47:07 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	read_heredoc(t_cmd *cmd, t_shell *shell, t_list *alloc_list)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	char	*line;
	int		i = 0;

	while (i < cmd->heredoc_count)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), 0);

		pid = fork();
		if (pid == -1)
			return (perror("fork"), 0);

		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL); // allow Ctrl+C to work in child
			signal(SIGQUIT, SIG_IGN);
			close(pipe_fd[0]);

			while (1)
			{
				line = readline("> ");
				if (!line || ft_strcmp(line, cmd->heredocs[i].delim) == 0)
				{
					free(line);
					break;
				}
				if (cmd->heredocs[i].expand)
					line = expand_token_value(line, shell, alloc_list);

				write(pipe_fd[1], line, ft_strlen(line));
				write(pipe_fd[1], "\n", 1);
				free(line);
			}
			close(pipe_fd[1]);
			exit(0); 
		}

		waitpid(pid, &status, 0);
		close(pipe_fd[1]);

		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);              
			close(pipe_fd[0]);
			shell->exit_status = 130;
			return (0);                     
		}

		if (i == cmd->heredoc_count - 1)
		{
			cmd->heredoc_fd = pipe_fd[0];
			cmd->heredoc_delim = cmd->heredocs[i].delim;
			cmd->heredoc_expand = cmd->heredocs[i].expand;
		}
		else
			close(pipe_fd[0]);

		i++;
	}
	return (1);
}
