/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testddd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:37:50 by hakader           #+#    #+#             */
/*   Updated: 2025/05/28 20:24:31 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	outfiless(t_shell *shell, char *outfile, int j)
{
	int	fd;
	int	flags;

	fd = -1;
	flags = O_WRONLY | O_CREAT;
	if (shell->cmds->append_flags[j])
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(outfile, flags, 0644);
	if (fd < 0)
		return (oi_err(outfile));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

int	infiless(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		return (oi_err(infile));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}



int	in_out(t_shell *shell)
{
	int		i;
	int		j;
	t_cmd	*cmd = shell->cmds;

	i = 0;
	while (cmd->rediriction[i])
	{
		j = 0;
		while (cmd->infiles && cmd->infiles[j])
		{
			if (ft_strcmp(cmd->rediriction[i], cmd->infiles[j]) == 0)
			{
				if (infiless(cmd->infiles[j]))
					return (1);
				break ;
			}
			j++;
		}
		j = 0;
		while (cmd->outfiles && cmd->outfiles[j])
		{
			if (ft_strcmp(cmd->rediriction[i], cmd->outfiles[j]) == 0)
			{
				if (outfiless(shell, cmd->outfiles[j], j))
					return (1);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
// int	outfilesssssss(t_shell *shell, char *outfile, int j)
// {
// 	int	fd;
// 	int	flags;

// 	flags = O_WRONLY | O_CREAT;
// 	if (shell->cmds->append_flags[j])
// 		flags |= O_APPEND;
// 	else
// 		flags |= O_TRUNC;

// 	fd = open(outfile, flags, 0644);
// 	if (fd < 0)
// 		return (oi_err(outfile));

// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		close(fd);
// 		return (oi_err(outfile));
// 	}

// 	close(fd);  // Close only the original, not the new dup'ed STDOUT
// 	return (EXIT_SUCCESS);
// }
// int	inn_out(t_shell *shell)
// {
// 	int		i, j;
// 	int		last_out_index = -1;
// 	t_cmd	*cmd = shell->cmds;

// 	// Apply the last infile that exists in redirection
// 	for (i = 0; cmd->infiles && cmd->infiles[i]; i++)
// 	{
// 		for (j = 0; cmd->rediriction && cmd->rediriction[j]; j++)
// 		{
// 			if (ft_strcmp(cmd->rediriction[j], cmd->infiles[i]) == 0)
// 			{
// 				if (infiless(cmd->infiles[i]))
// 					return (1);
// 			}
// 		}
// 	}

// 	// Find the LAST matching outfile in redirection
// 	for (i = 0; cmd->outfiles && cmd->outfiles[i]; i++)
// 	{
// 		for (j = 0; cmd->rediriction && cmd->rediriction[j]; j++)
// 		{
// 			if (ft_strcmp(cmd->rediriction[j], cmd->outfiles[i]) == 0)
// 				last_out_index = i;
// 		}
// 	}

// 	// Apply only the last redirection
// 	if (last_out_index != -1)
// 	{
// 		if (outfilesssssss(shell, cmd->outfiles[last_out_index], last_out_index))
// 			return (1);
// 	}

// 	return (0);
// }
