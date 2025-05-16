/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:06:12 by hakader           #+#    #+#             */
/*   Updated: 2025/05/16 18:16:22 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	open_all_infiles(char **infiles)
{
	int (fd), (i), (error);
	fd = -1;
	i = 0;
	error = 0;
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
	return (error);
}

int	open_all_outfiles(char **outfiles, int *append_flags)
{
	int (fd), (i), (flags), (error);
	error = 0;
	i = 0;
	fd = -1;
	while (outfiles && outfiles[i])
	{
		flags = O_WRONLY | O_CREAT;
		if (append_flags[i])
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
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
	return (error);
}
