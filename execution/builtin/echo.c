/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:08:28 by hakader           #+#    #+#             */
/*   Updated: 2025/05/13 10:28:37 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"


int open_and_write(t_cmd *cmd, int flag, int i)
{
	int fd = -1;
	int j = 0;

	while (cmd->outfiles && cmd->outfiles[j])
	{
		int flags = O_WRONLY | O_CREAT;
		if (cmd->append_flags[j] == 1)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;

		int temp_fd = open(cmd->outfiles[j], flags, 0644);
		if (temp_fd == -1)
		{
			perror(cmd->outfiles[j]);
			return (1);
		}
		if (cmd->outfiles[j + 1] == NULL)
			fd = temp_fd;
		else
			close(temp_fd);
		j++;
	}

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
int	execute_echo(t_cmd *cmd)
{
	int (i), (n_flag);
	i = 1;
	n_flag = 0;
	while (cmd->args[i] && is_new_line(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
	if (cmd->infiles || cmd->outfiles)
		return (open_and_write(cmd, n_flag, i));
	while (cmd->args[i])
	{
		// if (cmd->args[i] && ft_strcmp(cmd->args[1], "$?") == 0)
		// {
		// 	printf("%d\n", exit_status);
		// 	i++;
		// }
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (EXIT_SUCCESS);
}
