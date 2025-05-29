/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:06:12 by hakader           #+#    #+#             */
/*   Updated: 2025/05/28 20:26:09 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	oi_err(char *err)
{
	ft_putstr_fd("minishell: ", 2);
	perror(err);
	return (EXIT_FAILURE);
}

// int	open_all_infiles(t_shell *shell)
// {
// 	int (fd), (i);
// 	fd = -1;
// 	i = 0;
// 	while (shell->cmds->infiles && shell->cmds->infiles[i])
// 	{
// 		fd = open(shell->cmds->infiles[i], O_RDONLY);
// 		if (fd < 0)
// 			return (oi_err(shell->cmds->infiles[i]));
// 		else
// 		{
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 		}
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }

// int	open_all_outfiles(t_shell *shell)
// {
// 	int (fd), (i), (flags);
// 	i = 0;
// 	fd = -1;
// 	while (shell->cmds->outfiles && shell->cmds->outfiles[i])
// 	{
// 		flags = O_WRONLY | O_CREAT;
// 		if (shell->cmds->append_flags[i])
// 			flags |= O_APPEND;
// 		else
// 			flags |= O_TRUNC;
// 		fd = open(shell->cmds->outfiles[i], flags, 0644);
// 		if (fd < 0)
// 			return (oi_err(shell->cmds->outfiles[i]));
// 		else
// 		{
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }

// void	open_out(t_shell *shell)
// {
// 	int	fd;

// 	if (shell->cmds->outfiles && shell->cmds->outfiles[0])
// 	{
// 		fd = open(shell->cmds->outfiles[0], O_CREAT, 0664);
// 		if (fd < 0)
// 		{
// 			perror(shell->cmds->outfiles[0]);
// 			shell->exit_status = 1;
// 			return ;
// 		}
// 		close(fd);
// 	}
// 	shell->exit_status = 0;
// }

int	check_all_infiles(char **infiles)
{
	int		i;
	int		fd;

	i = 0;
	while (infiles && infiles[i])
	{
		fd = open(infiles[i], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(infiles[i], 2);
			ft_putstr_fd(": ", 2);
			perror("");
			return (EXIT_SUCCESS);
		}
		close(fd);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_all_outfiles(char **outfiles, int *append_flags)
{
	int		i;
	int		fd;
	int		flags;

	i = 0;
	while (outfiles && outfiles[i])
	{
		flags = O_WRONLY | O_CREAT;
		if (append_flags && append_flags[i])
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(outfiles[i], flags, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(outfiles[i], 2);
			ft_putstr_fd(": ", 2);
			perror("");
			return (EXIT_SUCCESS);
		}
		close(fd);
		i++;
	}
	return (EXIT_SUCCESS);
}
