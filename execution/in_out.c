/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:06:12 by hakader           #+#    #+#             */
/*   Updated: 2025/05/23 10:43:25 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	oi_err(char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	open_all_infiles(t_shell *shell)
{
	int (fd), (i), (error);
	fd = -1;
	i = 0;
	error = 0;
	while (shell->cmds->infiles && shell->cmds->infiles[i])
	{
		fd = open(shell->cmds->infiles[i], O_RDONLY);
		if (fd < 0)
		{
			oi_err(shell->cmds->infiles[i]);
			error = 1;
		}
		else
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		i++;
	}
	return (error);
}

int	open_all_outfiles(t_shell *shell)
{
	int (fd), (i), (flags), (error);
	error = 0;
	i = 0;
	fd = -1;
	while (shell->cmds->outfiles && shell->cmds->outfiles[i])
	{
		flags = O_WRONLY | O_CREAT;
		if (shell->cmds->append_flags[i])
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(shell->cmds->outfiles[i], flags, 0644);
		if (fd < 0)
		{
			oi_err(shell->cmds->outfiles[i]);
			error = 1;
		}
		else
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		i++;
	}
	return (error);
}
