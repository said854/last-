/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:08:28 by hakader           #+#    #+#             */
/*   Updated: 2025/05/19 18:02:26 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_new_line(char *arg)
{
	int	j;

	j = 1;
	if (arg[0] != '-' || arg[1] != 'n')
		return (EXIT_SUCCESS);
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (EXIT_FAILURE);
}

int	handle_outfiles(t_cmd *cmd, int *fd)
{
	int	j;
	int	flags;
	int	temp_fd;

	j = 0;
	while (cmd->outfiles && cmd->outfiles[j])
	{
		flags = O_WRONLY | O_CREAT;
		if (cmd->append_flags[j] == 1)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		temp_fd = open(cmd->outfiles[j], flags, 0644);
		if (temp_fd == -1)
		{
			perror(cmd->outfiles[j]);
			return (1);
		}
		if (cmd->outfiles[j + 1] == NULL)
			*fd = temp_fd;
		else
			close(temp_fd);
		j++;
	}
	return (0);
}

int	open_and_write(t_cmd *cmd, int flag, int i)
{
	int	fd;

	fd = -1;
	if (handle_outfiles(cmd, &fd))
		return (1);
	if (fd == -1)
		return (EXIT_FAILURE);
	while (cmd->args[i])
	{
		write(fd, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (flag == 0)
		write(fd, "\n", 1);
	close(fd);
	return (EXIT_SUCCESS);
}
int open_infile(char **infiles)
{
	int	fd;
	int	i;
	int	error;

	fd = -1;
	i = 0;
	error = 0;
	while (infiles && infiles[i])
	{
		fd = open(infiles[i], O_RDONLY);
		if (fd < 0)
		{
			perror(infiles[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	execute_echo(t_cmd *cmd)
{
	int	i, n_flag;

	i = 1;
	n_flag = 0;

	if (cmd->infiles && open_infile(cmd->infiles))
	{
		return 1;
	}
	while (cmd->args[i] && is_new_line(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
	if (cmd->outfiles)
		return (open_and_write(cmd, n_flag, i));

	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");

	return (EXIT_SUCCESS);
}


